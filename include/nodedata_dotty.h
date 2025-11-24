#ifndef _NODEDATA_DOTTY_H_
#define _NODEDATA_DOTTY_H_

#include "nodedata.h"

template< symbol_list a, symbol_id n >
class nodedata_dotty {
protected:
	const nodedata<a,n> &_n;
public:
	nodedata_dotty(const nodedata<a,n> &nd): _n(nd) {};
};

template< symbol_list a, symbol_id n >
class nodedata_dotty_simple: public nodedata_dotty<a,n> {
public:
	nodedata_dotty_simple(const nodedata<a,n> &nd): nodedata_dotty(nd) {};

	friend ostream &operator<<(ostream &os, const nodedata_dotty_simple &nd) {
		os << nd._n.size();
	}
};

template< symbol_list a, symbol_id n >
class nodedata_dotty_complex: public nodedata_dotty<a,n> {
private:
	const nodedata<a,n> &_n;
public:
	nodedata_dotty_complex(const nodedata<a,n> &nd): nodedata_dotty(n) {};

	friend ostream &operator<<(ostream &os, const nodedata_dotty_complex &nd) {
		for (size_t i = 0; i < n; i++) {
			os << "{" << nd._b.org[i].size() << "}";
			if (i + 1 < n) os << "|";
		}
	}
};

template< symbol_list a, symbol_id n >
class nodedata_dotty_complete: public nodedata_dotty<a,n> {
public:
	nodedata_dotty_complete(const nodedata<a,n> &n): nodedata(n) {};

	friend ostream &operator<<(ostream &os, const nodedata_dotty_complete &nd) {
		for (size_t i = 0; i < n; i++) {
			os << "{" << nd._b.org[i].size() << "|"
			   << nd._b.org[i] << "}";
			if (i + 1 < n) os << "|";
		}
	}
};

#endif /* _NODEDATA_DOTTY_H_ */
