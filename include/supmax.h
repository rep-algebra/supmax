#ifndef __SUBMAX_H
#define __SUBMAX_H

#include <stdexcept>
#include <ostream>
#include "ntree.h"
#ifdef _SUPMAX_SHOW_H_
#include "ntree_show.h"
#endif /* _SUPMAX_SHOW_H_ */
#include "alphabet.h"
#include "nodedata.h"
#include <map>
#include <set>
#include "statics.h"

template< symbol_list a, symbol_id n, statics &_stat >
class Supmax {
public:
	typedef alphabet<a, n>					Alpha;
	typedef	nodedata< a, n >				Node_data;
	typedef NTree_basic< n, Node_data, statics, _stat >	Tree;
	typedef NSubTree_basic< n, Node_data, statics, _stat >	SubTree;
	typedef SubTree::Node					Node;
	typedef SubTree::Node_pointer				Node_pointer;
	typedef Tree::iterator					Iterator;
	typedef set<Node_pointer>				SupmaxSet;
private:
	seq_set		S;
	seq_name_map	S_name;

	SupmaxSet	supmaxs;
	
	Tree		idx;
	size_t		coverage;
public:
	Supmax(size_t _coverage = 1)
	: coverage(_coverage) { };

	void set_coverage(size_t _coverage) {
		coverage = _coverage;
	}

	void insert(const seq &_s, const string &name = string()) {
		seq_set_c_iterator id = S.insert(S.end(), _s);
		seq_c_iterator i;

		try {
			for (i = _s.begin(); i != _s.end(); i++) {
				insert(id, i, _s.end());
			}
			S_name.insert(make_pair(id, name));
		}
		catch(std::exception &e) {
			cerr << e.what() << ":" << size_t(i - _s.begin()) << endl;
		}
	}

	void insert(const seq_set_c_iterator id,
	            const seq_c_iterator begin,
	            const seq_c_iterator end) {

		if (begin == end) return;

		pair<SubTree, string::const_iterator> itr =
			idx.brand_break(begin, end, Alpha());

		SubTree	&st = itr.first;
		(*st).complete();
		symbol		c   = *itr.second;
		symbol_id	s   = Alpha()(c);
		subseq_set	&ss = (*st).org[s];

		itr.second++;
		ss.push_front(subseq(id, begin, itr.second));

		if ((*st).issupermaximal(coverage)) {
			supmaxs.erase(st.node);
			_stat.supermaximal = supmaxs.size();
		}

		expand(s, st);

		(*st).purify();
	}

	void expand(symbol_id s, SubTree src) throw (std::exception) {
		supmaxs.erase(src.node);
		if (s != 0) {
			if ((*src).expandible(s, coverage)) {
				(*(src[s])).expandtome(s, *src);
				for (size_t i = 0; i < n; i++) expand(i, src[s]);
			}
		}
		if (src.isleaf() && (*src).issupermaximal(coverage)) {
			supmaxs.insert(src.node);
		}
		_stat.supermaximal = supmaxs.size();
		(*src).purify();
	}

	string name_of(const seq_set_c_iterator &id) {
		return S_name[id];
	}

	void supmax(ostream &os) {
		for(SupmaxSet::const_iterator i = supmaxs.begin();
		    i != supmaxs.end(); i++) {
			os << (*i)->data.str() << ":";
			os << (*i)->data.size() << ":";
			for (size_t j =0; j < n; j++)
				os << subseq_set_format(S_name, (*i)->data.org[j]);
			os << endl;
		}
	}

	void supmax(subseq_map &map) {
		for(Tree::iterator i = idx.begin(); i != idx.end(); i++) {
			if (i.isleaf() && (*i).size() > 0
			    && (*i).issupermaximal(coverage))
			for (size_t ii = 0; ii < n; ii++)
				map[(*i).str()].insert(map[(*i).str()].begin(), (*i).org[ii].begin(), (*i).org[ii].end());
		}
	}

	void supmax(subseq_set &lst) {
		for(Tree::iterator i = idx.begin(); i != idx.end(); i++) {
			if (i.isleaf() && (*i).size() > 0
			    && (*i).issupermaximal(coverage))
			for (size_t ii = 0; ii < n; ii++)
				lst.insert(lst.begin(), (*i).org[ii].begin(), (*i).org[ii].end());
		}
	}

	const statics &getstatics() const {
		return _stat;
	}

#ifdef _DOTTY_H_
	friend
	Dotty &draw(Dotty &_dot, const Supmax<a,n> &_sm) {
#if defined(_TREE_MODE_COMPLEX_) || defined(_TREE_MODE_COMPLETE_)
		_dot.node("","","record");
#else
		_dot.node("","","circle");
#endif
		draw(_dot, _sm.idx, Supmax<a,n>::Alpha());
		return _dot;
	}
#endif /* _DOTTY_H_ */
	
#ifdef _SUPMAX_SHOW_H_
	typedef Tree::Node_pointer				node_t;
	typedef supmax_format< node_t, seq_name_map, Alpha >	format_t;
	typedef ntree_show< n, Node_data, statics, _stat, format_t >	show_t;

	show_t show(int flags = 0)
	{
		format_t format(S_name, Alpha(), flags);
		return show_t( idx, format );
	};
	ostream &show(ostream &os, int flags = 0)
	{
		format_t format(S_name, Alpha(), flags);
		os << show_t( idx, format );
		return os;
	};
#endif

};

#endif /* __SUBMAX_H */

