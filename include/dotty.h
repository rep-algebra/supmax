#ifndef _DOTTY_H_
#define _DOTTY_H_

#include <string>
#include <iostream>

using namespace std;

class Dotty
{
private:
	ostream &_os;
public:
	void begin_attrib() { _os << " [ "; } 
	void end_attrib() { _os << " ] " << endl; } 
	void spc_attrib() { _os << ", "; } 

	template <class L>
	void label(const L &l) { _os << " label = \"" << l << "\" "; }

	template <class L, class LF>
	void label(const L &l, const LF &lf)
	{ _os << " label = \"" << lf(l) << "\" "; }

	template <class L>
	void shape(const L &s) { _os << " shape = \"" << s << "\" "; }

	Dotty(ostream &os): _os(os) {
		_os << "digraph G {" << endl;
	}
	~Dotty() {
		_os << "}" << endl;
	}
	void setsize(double w, double h) {
		_os << "size=\"" << w << "," << h << "\"" << endl;
	}
	template <class K, class L>
	void node(K n, L l, const string &_shape) {
		_os << "node" << n;
		begin_attrib();
			label(l);
			if (!_shape.empty()) shape(_shape);
		end_attrib();
	}
	/*
	template <class K, class L, class F>
	void node(K n, L l, F f, const string &_shape) {
		_os << "node" << n;
		begin_attrib();
			label(f[l]);
			if (!_shape.empty()) shape(_shape);
		end_attrib();
	}
	*/
	template <class Itr>
	void node(Itr begin, Itr end) {
		if (begin == end) return;
		_os << "node" << *begin;
		begin++;
		while(begin != end) {
			_os << " -> node" << *begin;
			begin++;
		}
		_os << endl;
	}
	void record_begin(int n) {
		_os << n;
		begin_attrib();
			shape("record");
			spc_attrib();
		_os << " label = \"";
	}
	void record_beginrow() { _os << '{'; }
	void record_endrow() { _os << '}'; }
	void record_item(int id, string l) {
			_os << '<' << id << '>';
			_os << l;
	}
	void record_spc() { _os << '|'; }
	void record_end() {
		_os << '\"';
		end_attrib();
	}
	template <class K, class E>
	void edge(K o, K d, E name = E()) {
		_os << "node" << o << " -> node" << d;
		begin_attrib();
			label(name);
		end_attrib();
	}
};

#endif

