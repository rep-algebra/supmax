#ifndef __SEQ_H
#define __SEQ_H

#include "../config.h"
#include <ext/slist>
#include <map>
#include <string>
#include <set>
#include "types.h"

typedef std::string			seq;
typedef seq::iterator			seq_iterator;
typedef seq::const_iterator		seq_c_iterator;

typedef	std::slist<seq, malloc_alloc>			seq_set;
typedef	seq_set::iterator		seq_set_iterator;
typedef	seq_set::const_iterator		seq_set_c_iterator;

struct seq_set_c_iterator_compare {
	bool operator() (const seq_set_c_iterator &a, 
			 const seq_set_c_iterator &b) const {
		return (*a < *b);
	}
};

typedef map<const seq_set_c_iterator, string, seq_set_c_iterator_compare>
	seq_name_map;


struct subseq_l {
	seq_set_c_iterator	sequence;
	seq_c_iterator		_begin;
	seq_c_iterator		_end;

	subseq_l(const seq_set::const_iterator &_sequence,
	       const seq_c_iterator &__begin,
	       const seq_c_iterator &__end)
	: sequence(_sequence),
	  _begin(__begin),
	  _end(__end) { };

	seq_c_iterator	begin() const { return _begin; }
	seq_c_iterator	end() const { return _end; }
	seq_c_iterator	begin(int i) { _begin += i; return _begin; }
	seq_c_iterator	end(int i) { _end += i; return _end; }
	size_t pbegin() const { return _begin - sequence->begin(); }
	size_t pend() const { return _end - sequence->end(); }
	seq str() const { return seq(begin(), end()); }
	seq str_() const { return seq(begin(), end() - 1); }
	bool haveprev() const { return _begin != sequence->begin(); }
	symbol prev() const { return *(_begin - 1); }
};

struct subseq_s {
#ifdef _PREV_
	symbol			_prev;
#else
	seq_set_c_iterator	sequence;
#endif
	unsigned short int	_begin;
	unsigned short int	_end;

	subseq_s(const seq_set::const_iterator &_sequence,
	       const seq_c_iterator &__begin,
	       const seq_c_iterator &__end)
#ifdef _PREV_
	: _prev(*(__begin-1)),
#else
	: sequence(_sequence),
#endif
	  _begin(__begin - _sequence->begin()),
	  _end(__end - _sequence->begin()) { };

#ifdef _PREV_
	void begin(int i) { _begin += i; }
	void end(int i) { _end += i; }
#else
	seq_c_iterator	begin() const { return sequence->begin() + _begin; }
	seq_c_iterator	end() const { return sequence->begin() + _end; }
	seq_c_iterator	begin(int i) { _begin += i; return begin(); }
	seq_c_iterator	end(int i) { _end += i; return end(); }
	seq str() const { return seq(begin(), end()); }
	seq str_() const { return seq(begin(), end() - 1); }
#endif
	size_t pbegin() const { return _begin; }
	size_t pend() const { return _end; }
	bool haveprev() const { return _begin > 0; }
#ifdef _PREV_
	symbol prev() const { return _prev; }
#else
	symbol prev() const { return *(begin() - 1); }
#endif
};

typedef subseq_s	subseq;

typedef std::slist<subseq, malloc_alloc>		subseq_set;
typedef subseq_set::iterator		subseq_set_iterator;
typedef subseq_set::const_iterator	subseq_set_c_iterator;

typedef std::map<string,subseq_set, malloc_alloc>	subseq_map;
typedef subseq_map::iterator		subseq_map_iterator;
typedef subseq_map::const_iterator	subseq_map_c_iterator;

struct subseq_format {
	const seq_name_map	&M;
	const subseq 		&ss;
	subseq_format(const seq_name_map &_M, const subseq &_ss): M(_M), ss(_ss) { };
};

struct subseq_set_format {
	const seq_name_map	&M;
	const subseq_set	&ss;
	subseq_set_format(const seq_name_map &_M, const subseq_set &_ss): M(_M), ss(_ss) { };
};

typedef multimap<subseq_set_c_iterator, subseq_set_c_iterator> relation;

bool are_path(relation &, subseq_set_c_iterator &, subseq_set_c_iterator &);
void create_relation(relation &r, const subseq_set &_m);

#ifdef _DOTTY_H_
Dotty &draw(Dotty &, const string &, const subseq_map &,  const string &, const subseq_map &);
Dotty &draw(Dotty &, const subseq_map &);
Dotty &draw(Dotty &, const relation &);
#endif /* _DOTTY_H_ */

#ifdef _CPP_OSTREAM
std::ostream &operator<<(std::ostream &, const subseq &);
std::ostream &operator<<(std::ostream &, const subseq_set &);
std::ostream &operator<<(std::ostream &os, const subseq_format &_f);
std::ostream &operator<<(std::ostream &os, const subseq_set_format &_f);
#endif /* _CPP_IOSTREAM */

#endif /* __SEQ_H */

