// #define _TREE_MODE_SIMPLE_
// #define _TREE_MODE_COMPLEX_
#define _TREE_MODE_COMPLETE_

#include "../config.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <malloc.h>
#include <time.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/times.h>
#include <unistd.h>
#include "include/debug.h"
#include "include/statics.h"
#include "include/ntree_show.h"
#include "include/supmax_show.h"
#include "include/supmax_show.cc"
#include "include/supmax.h"
#include "include/fasta.h"
#include "include/raw.h"
#include "include/alphabet.h"
#include "clo.h"
#include <signal.h>

#define FLG_FULLSTATICS	1

ostream &operator<<(ostream &os, const struct timeval &tm) {
	os << tm.tv_sec + 1E-6 * tm.tv_usec;
	return os;
}

double operator-(const struct timeval &a, const struct timeval &b) {
	return (a.tv_sec + 1E-6 * a.tv_usec) - (b.tv_sec + 1E-6 * b.tv_usec);
}

statics Supmaxstat;

#ifdef ALPHA
symbol Latin[] = "*.+;:_?abcdefghijklmnñopqrstuvwxyzáéíóú";
typedef Supmax<Latin,sizeof(Latin),Supmaxstat>	TSupmax;
typedef alphabet<Latin, sizeof(Latin)>		TAlphabet;
#else
symbol DNA[] = ".ACTGN";
typedef Supmax<DNA,6,Supmaxstat>		TSupmax;
typedef alphabet<DNA, sizeof(DNA)>		TAlphabet;
#endif

int raw::id = 0;

size_t i_count;
istream *input = &cin;
ostream *stat = &cout;
ostream *supmax = &cout;
struct timeval start, end;
TSupmax SM;
TAlphabet Alphabet;
#ifdef CLO
clo::parser parser;
#endif
statics st;

struct aceptable {
	double _min;

	aceptable(double min): _min(min) {}

	template < class T >
	bool operator()(const T &t) const {
		return (t.first.size() * t.second.size() > _min);
	}
};

void result(int i = 0) {
#ifdef CLO
	const clo::options &options = parser.get_options();
#endif

	cout << "Terminating" << endl;
	*stat << "#-------------------------------------" << endl
             << "# Cantidad: " << i_count << endl
             << "# Tiempo: " << end - start << endl
             << "#-------------------------------------" << endl;
	cout << "Almacenando supermaximales";
	SM.supmax(*supmax);
	cout << "." << endl;

#ifdef CLO
	if (!options.tree.empty()) {
		// Aqui nuevo código
		cout << "Dibujando el arbol";
		ofstream dot_tree(options.tree.c_str());
		dot_tree << "digraph G {" << endl;
		dot_tree << "size = \"6,6\"" << endl;
		dot_tree << "graph[" << endl
			 << "rankdir = \"LR\"" << endl
			 << "]" << endl;
		if (st.nodes < 100)
			dot_tree << SM.show(options.treeflag);
		else if (st.nodes < 500)
			dot_tree << SM.show(0);
		dot_tree << "}" << endl;
		cout << "." << endl;
	}
#endif

	if (i != SIGHUP) {
#ifdef CLO
		if (!options.input.empty())
			delete input;
		if (!options.statics.empty())
			delete stat;
		if (!options.supermaximals.empty())
			delete supmax;
#endif
		exit(0);
	}
}

template <class Container>
void insert(seqformat_inputiterator &f, Container &SM, statics &st, int flags = 0) {
#ifdef CLO
        const clo::options &options = parser.get_options();
#endif
	struct rusage  rusage;
	char mark[] = { Alphabet((symbol_id)0), 0 };

	cout << "Node data size in bytes: " << sizeof(Container::Node_data) << endl;
	cout << "Tree node size in bytes: " << sizeof(Container::Node) << endl;
	cout << "Subsequence size in bytes: " << sizeof(subseq) << endl;
	*stat << "#------------" << endl
             << "# Secuencias " << endl
             << "#------------" << endl
             << "# name\tlen\trtime\tutime\tstime\tmem\tnodes\tmaximals\tsupermaximals" << endl;

	i_count = 0;

	gettimeofday(&start,NULL);
	signal(SIGTERM,result);
	signal(SIGINT,result);
	signal(SIGQUIT,result);
	while(f.next()) {
		SM.insert(string(mark) + f.seq() + mark, f.name());
		cout << mark << f.seq() << mark << endl;
		gettimeofday(&end,NULL);
		getrusage(RUSAGE_SELF, &rusage);
		struct mallinfo info = mallinfo();
		i_count++;
		*stat << f.name() << "\t"
			<< f.seq().size() << "\t"
			<< end - start << "\t"
			<< rusage.ru_utime << "\t"
			<< rusage.ru_stime << "\t"
			<< info.usmblks + info.uordblks << "\t";
		if (flags & FLG_FULLSTATICS) {
			*stat << Supmaxstat.nodes << "\t"
			     << Supmaxstat.maximal << "\t"
			     << Supmaxstat.supermaximal << "\t"
			     << endl;
#ifdef CLO
			if (!options.treeprofile.empty()) {
				stringstream filename;
				filename << options.treeprofile.c_str()
				     << "." << f.name() << ".dot";
				ofstream dot_tree(filename.str().c_str());
				dot_tree << "digraph G {" << endl;
				dot_tree << "size = \"6,6\"" << endl;
				dot_tree << "graph[" << endl
				         << "rankdir = \"LR\"" << endl
				         << "]" << endl;
				if (st.nodes < 100)
					dot_tree << SM.show(
					   options.treeprofileflag);
				else if (st.nodes < 500)
					dot_tree << SM.show(0);
				dot_tree << "}" << endl;
			}
#endif
		} else {
			*stat << "-\t-\t-\t" << endl;
		}
	}
	signal(SIGTERM,NULL);
	signal(SIGINT,NULL);
	signal(SIGQUIT,NULL);
	signal(SIGHUP,NULL);
	result();

	return;
}

int main(int argc, char *argv[]) {
	seqformat_inputiterator *format = NULL;

#ifdef CLO
	int flags = 0;
	try {
		parser.parse(argc, argv);

		const clo::options &options = parser.get_options();

		if (!options.input.empty())
			input = new ifstream(options.input.c_str());

		if (!options.statics.empty())
			stat = new ofstream(options.statics.c_str());

		if (!options.supermaximals.empty())
			supmax = new ofstream(options.supermaximals.c_str());

		if (options.fullstat)
			flags |= FLG_FULLSTATICS;

		if (!options.format.empty()) {
			if (options.format == "raw") format = new raw(*input);
			if (options.format == "fasta") format = new fasta(*input);
		}
		assert(format != NULL);

		set_debug(options.debug);
		SM.set_coverage(options.coverage);

		insert(*format, SM, st, flags);
		delete format;
		result();
	} catch (clo::autoexcept &e) {
		switch (e.get_autothrow_id()) {
		case clo::autothrow_help:
			std::cout << "Usage: " << argv[0] << " [options]" << endl;
			std::cout << e.what();
			return 0;
		}
	} catch (std::exception &e) {
		std::cerr << argv[0] << ": " << e.what() << endl;
		return 1;
	} catch (...) {
		std::cerr << "Exception!" << endl;
	}
#else
	SM.set_coverage(10);
	format = new fasta(*input);
	insert(*format, SM, st, FLG_FULLSTATICS);
	delete format;
#endif

	return 0;
}

