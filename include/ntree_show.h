#ifndef _NTREE_SHOW_H_
#define _NTREE_SHOW_H_

#include <ostream.h>
#include "ntree.h"

template <typename T>
class basic_format {
public:
	typedef T	Type;
public:
	basic_format() { };
	~basic_format() { };

	void node(ostream &os, const Type a) const {
		os << "node" << a << endl;
	};
	void edge(ostream &os, const Type a,
	                       const Type b, const size_t l) const {
		os << "node" << a << " -> node" << b <<
		      " [ label=\"" << l << "\" ]" << endl;
	};
};

template < size_t n, typename T, typename C, C &_cont, typename F >
class ntree_show {
public:
	typedef NSubTree_basic<n, T, C, _cont>	Tree;
	typedef F			Format;
private:
	const Tree	_tree;
	const Format	_format;
public:
	ntree_show(const Tree &tree, const Format &format = Format() ) 
		: _tree(tree), _format(format) { };

	ntree_show(const ntree_show &t ) 
		: _tree(t._tree), _format(t._format) { };

	~ntree_show( ) { };

	friend ostream &operator<<(ostream &os, const ntree_show &o) {
		o._format.node(os, o._tree.node);
		for (size_t i = 0; i < n; i++)
			if ( o._tree.exist(i) ) {
				o._format.edge(os, o._tree.node, o._tree.node->soon[i], i );
				os << ntree_show(o._tree[i], o._format);
			}
		return os;
	}
};

#endif /* _NTREE_SHOW_H_ */
