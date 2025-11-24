#ifndef __NODEDATA_H
#define __NODEDATA_H

#include <ext/slist>
#include "alphabet.h"
#include "seq.h"

// #define PURIFY

template< symbol_list a, symbol_id n >
struct nodedata {
	typedef alphabet<a,n>	Alpha;
#ifdef PURIFY
	subseq_set	*org;
#else
	subseq_set	org[n];
#endif

	nodedata() {
#ifdef PURIFY
		org = NULL;
#endif
	}

	~nodedata() {
#ifdef PURIFY
		delete[] org;
		org = NULL;
#endif
	}

	size_t size(symbol_id i = 0) const {
		if (org == NULL) return 0;
		size_t s = 0;
		for(; i < n; i++) s += org[i].size();
		return s;
	}

	size_t alpha_size() const {
		return n;
	}

#ifdef _PREV_
	seq str() const {
		return seq();
	}
#else
	seq str() const {
		if (org == NULL) return seq();
		for(symbol_id i = 0; i < n; i++)
			if (org[i].size() >= 1)
			return seq(org[i].begin()->begin(),
			           org[i].begin()->end() - 1);
		return seq();
	}
#endif

	bool expandible(symbol_id s, size_t coverage) const {
		return (org != NULL && org[s].size() > coverage);
	}

	bool issupermaximal(size_t coverage) const {
		if (org == NULL) return false;
		size_t bag[n] = {0};

		for (symbol_id i = 0; i < n; i++) {
			for (subseq_set_c_iterator j = org[i].begin();
		             j != org[i].end(); j++) {
				/*
				seq_c_iterator b = j->begin();
				if (b != j->sequence->begin()) {
					--b;
					symbol_id c = Alpha()(*b);
					bag[c]++;
					if (c != 0 && bag[c] > coverage) {
						return false;
					}
				}
				*/
				if (j->haveprev()) {
					symbol_id c = Alpha()(j->prev());
					bag[c]++;
					if (c != 0 && bag[c] > coverage)
						return false;
				}
			}
		}

		return true;
	}

	void complete() {
#ifdef PURIFY
		if (org == NULL) {
			org = new subseq_set[n];
			assert(org != NULL);
		}
#endif
	}

	void purify() {
#ifdef PURIFY
		if (size(1) == 0) {
			delete[] org;
			org = NULL;
		}
#endif
	}

#ifdef _PREV_
	void expandtome(subseq_set &src, const seq &_seq) {
		subseq_set_iterator i = src.pbegin();
		complete();
		while (i != src.end()) {
			symbol_id sym = Alpha()(_seq[i->pend()]);
			subseq_set &obj = org[sym];
			i->end(1);
			obj.splice(obj.begin(), src, i);
			i = src.begin();
		}
		purify();
	}
#else
	void expandtome(subseq_set &src) {
		subseq_set_iterator i = src.begin();
		complete();
		while (i != src.end()) {
			symbol_id sym = Alpha()(*i->end());
			subseq_set &obj = org[sym];
			i->end(1);
			obj.splice(obj.begin(), src, i);
			i = src.begin();
		}
		purify();
	}
#endif

	void expandtome(symbol_id sym, nodedata &src) {
		if (src.org != NULL) expandtome(src.org[sym]);
	}

#ifdef _CPP_OSTREAM
	friend
	ostream &operator<<(ostream &os, const nodedata &_b) {
		if (src.org == NULL) {
			os << _b.size();
			return os;
		}
#if defined(_TREE_MODE_SIMPLE_)
		os << _b.size();
#elif defined(_TREE_MODE_COMPLEX_)
		for (size_t i = 0; i < n; i++) {
			os << "{" << _b.org[i].size() << "}";
			if (i + 1 < n) os << "|";
		}
#elif defined(_TREE_MODE_COMPLETE_)
		for (size_t i = 0; i < n; i++) {
		os << "{" << _b.org[i].size() << "|"
		   << _b.org[i] << " }";
			if (i + 1 < n) os << "|";
		}
#endif /* defined */
		return os;
	}

	friend
	ostream &operator<<(ostream &os, const std::slist<nodedata> &_b) {
		os << *_b;
		return os;
	}
#endif 
	
};

#endif /* __NODEDATA_H */

