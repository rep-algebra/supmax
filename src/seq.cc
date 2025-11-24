#include <ostream>
#include "include/dotty.h"
#include "include/seq.h"

std::ostream &operator<<(std::ostream &os, const subseq &_ss) {
	os << &(*(_ss.sequence)) << ":"
	   << _ss.str() << "("
	   << _ss.pbegin() << ","
	   << _ss.pend() << ")";
	return os;
}

std::ostream &operator<<(std::ostream &os, const subseq_format &_f) {
	        os << "<" << _f.M.find(_f.ss.sequence)->second << ","
	           << _f.ss.pbegin() << ","
        	   << _f.ss.pend() << ">";
	        return os;
}

std::ostream &operator<<(std::ostream &os, const subseq_set &_b) {
	if (_b.begin() == _b.end())
		return os;
	subseq_set::const_iterator i = _b.begin();
	os << *i; i++;
	for (; i != _b.end(); i++)
		os << "|" << *i;
	return os;
}

std::ostream &operator<<(std::ostream &os, const subseq_set_format &_f) {
	if (_f.ss.begin() == _f.ss.end())
		return os;
	subseq_set::const_iterator i = _f.ss.begin();
	os << subseq_format(_f.M, *i); i++;
	for (; i != _f.ss.end(); i++)
		os << " " <<  subseq_format(_f.M, *i);
	return os;
}

bool operator<(const subseq_set_c_iterator &a, const subseq_set_c_iterator &b) {
       	return (&(a) < &(b));
}

bool are_path(relation &r, subseq_set_c_iterator &a, subseq_set_c_iterator &b) {
	pair<relation::iterator,relation::iterator> itr = r.equal_range(a);
	for(;itr.first != itr.second; itr.first++) {
		if (itr.first->second != b)
			return are_path(r,itr.first->second,b);
	}
	return false;
}

void create_relation(relation &r, const subseq_set &_m) {
	for (subseq_set_c_iterator i = _m.begin(); i != _m.end();)
	for (subseq_set_c_iterator j = ++i; j != _m.end(); j++)
		if (i->sequence == j->sequence && i->end() < j->begin() &&
		    !are_path(r, i, j)) {
			cout << ".";
			r.insert(make_pair(i,j));
		}
	cout << endl;
}

Dotty &draw(Dotty &_dot, const relation &r) {
	for (relation::const_iterator i = r.begin(); i != r.end(); i++)
		_dot.edge((*i).first->str_(), (*i).second->str_(), &*(i->first->sequence));
	return _dot;
}

Dotty &draw(Dotty &_dot, const string &_ns, const subseq_set &_n, const string &_ms, const subseq_set &_m) {
	for (subseq_set_c_iterator i = _n.begin(); i != _n.end(); i++)
	for (subseq_set_c_iterator j = _m.begin(); j != _m.end(); j++)
		if (i->sequence == j->sequence && i->end() < j->begin())
			_dot.edge(_ns, _ms, &(*i->sequence));
	return _dot;
}

Dotty &draw(Dotty &_dot, const subseq_map &_m) {
	for (subseq_map_c_iterator i = _m.begin(); i != _m.end();) {
		_dot.node(i->first,i->first,"box");
		for (subseq_map_c_iterator j = ++i; j != _m.end(); j++)
			draw(_dot, i->first, i->second, j->first, j->second);
	}
	return _dot;
}

