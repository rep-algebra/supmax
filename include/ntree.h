#ifndef __NTREE_H
#define __NTREE_H

#include <stack>
#include <function.h>
#include <stdexcept>

using namespace std;

template < size_t n, class T >
struct __NTree_node_basic {
	__NTree_node_basic *soon[n];
	T data;

	__NTree_node_basic()
	: data() {
		memset(soon, 0, sizeof(soon));
	}

	__NTree_node_basic(const T& _data)
	: data(_data) {
		memset(soon, 0, sizeof(soona));
	}

	__NTree_node_basic(const __NTree_node_basic& _x)
	: data(_x._data) {
		memcpy(soon, _x.soon, sizeof(soon));
	}

	__NTree_node_basic &operator=(const __NTree_node_basic& _x) { 
		data = _x.data;
		memcpy(soon, _x.soon, sizeof(soon));
	}

	~__NTree_node_basic()
	{ }

	void _duplicate_chain_soon(const __NTree_node_basic &_x) {
		data = _x.data;
		for (size_t i = 0; i < n; i++) {
			if (_x[i].soon[i] != NULL) {
				soon[i] = new __NTree_node_basic();
				soon[i]->_duplicate_chain_soon(*_x.soon[i]);
			}
		}
	}

	void _delete_chain_soon() {
		for (size_t i = 0; i < n; i++) {
			if (soon[i] != NULL) soon[i]->_delete_chain_soon();
			delete soon[i]; }
	}
};

template < size_t n, class T >
struct __NTree_status {
	__NTree_node_basic< n, T > *node;
	size_t i;
	__NTree_status(__NTree_node_basic< n, T > *_node, size_t _i):
		node(_node), i(_i) {}

	bool operator==(const struct __NTree_status &_x) const {
		return (node == _x.node) && (i == _x.i);
	}

	bool operator!=(const struct __NTree_status &_x) const {
		return (node != _x.node) || (i != _x.i);
	}
};

template < size_t n, class T, size_t lim = n, size_t ini = 0 >
struct __NTree_iterator_basic {
	stack< struct __NTree_status< n, T > > status;

	__NTree_iterator_basic() {
	}

	__NTree_iterator_basic(__NTree_node_basic< n, T > *node ) {
		__NTree_status< n, T > actual(node, ini);
		status.push(actual);
	}

	void _M_next() {
		while (!status.empty()) {
			__NTree_status< n, T > actual = status.top();

			while (status.top().i != lim) {
				if (actual.node->soon[status.top().i] != NULL) {
					actual.node 
					= actual.node->soon[status.top().i];
					actual.i = ini;
					status.push(actual);
					return;
				}
				status.top().i++;
			}
			status.pop();
			if (!status.empty()) status.top().i++;
		}
	}

	__NTree_iterator_basic &operator++() { _M_next(); return *this; };

	__NTree_iterator_basic &operator++(int) { _M_next(); return *this; };

	const T &operator*() const { return status.top().data; }
	T &operator*() { return status.top().node->data; }

	bool operator==(const struct __NTree_iterator_basic &_x) const {
		return status == _x.status;
	}

	bool operator!=(const struct __NTree_iterator_basic &_x) const {
		return status != _x.status;
	}

	bool isleaf() const {
		bool r = true;
		__NTree_node_basic< n, T > *node = status.top().node;
		for(size_t i = 0; r && i < n; i++)
			r &= (node->soon[i] == NULL);
		return r;
	}

};

template < size_t n, typename T, typename C, C &_cont >
class NSubTree_basic {
public:
	typedef __NTree_node_basic< n, T >		Node;
	typedef Node*					Node_pointer;
	typedef __NTree_iterator_basic< n, T >	iterator;

	Node_pointer	node;
public:
	NSubTree_basic(Node_pointer _node): node(_node) {};
	virtual ~NSubTree_basic() {};

	iterator begin() { return iterator(node); }

	iterator end() { return iterator(); }

	NSubTree_basic operator[] (size_t i) {
		if (!(i < n)) throw range_error("Children out of range.");
		if (node->soon[i] == NULL) {
		       node->soon[i] = new Node;
		       _cont.newnode();
		}
		return NSubTree_basic(node->soon[i]);
	}

	Node_pointer operator()() { return node; }

	const NSubTree_basic operator[] (size_t i) const {
		if (!(i < n)) throw range_error("Children out of range.");
		return NSubTree_basic(node->soon[i]);
	}

	bool exist(size_t i) const {
		assert(node != NULL);
		return ((i < n) && node->soon[i] != NULL);
	}

	bool noexist(size_t i) const {
		assert(node != NULL);
		return (!(i < n) && node->soon[i] == NULL);
	}

	bool isleaf() const {
		bool r = true;
		for(size_t i = 0; r && i < n; i++)
			r &= (node->soon[i] == NULL);
		return r;
	}

	template <class I, class F >
	NSubTree_basic brand(const I &begin, const I &end, const F &f = id) {
		NSubTree_basic tmp = *this;
		for (I i = begin; i != end; i++)
			tmp = tmp[f(*i)];
		return tmp;
	}

	template <class I, class F>
	const NSubTree_basic &brand(const I &begin, const I &end, const F &f = id) const {
		NSubTree_basic tmp = *this;
		for (I i = begin; i != end; i++)
			tmp = tmp[f(*i)];
		return tmp;
	}

	template <class I, class F>
	pair< NSubTree_basic, const I >
	brand_break(I i, const I &end, const F &f = id) {
		NSubTree_basic tmp = *this;
		for (; i != end && tmp.exist(f(*i)); i++) {
			tmp = tmp[f(*i)];
		}
		return make_pair(tmp, i);
	}

	template <class I, class F>
	pair< const NSubTree_basic &, const I &>
	brand_break(I i, const I &end, const F &f = id) const {
		NSubTree_basic tmp = *this;
		for (; i != end && tmp.exist(f(*i)); i++)
			tmp = tmp[f(*i)];
		return make_pair(tmp, i);
	}

	T &operator* () {
		return node->data;
	}

	const T &operator* () const {
		return node->data;
	}

#ifdef _DOTTY_H_
	template < class F >
	friend
	Dotty &draw(Dotty &_dot,
	            const NSubTree_basic<n,T> &_tree,
		    const F &f) {
		_dot.node( _tree.node, *_tree );
		for (size_t i = 0; i < n; i++)
			if ( _tree.exist(i) ) {
				_dot.edge( _tree.node,
					   _tree.node->soon[i], f(i) );
				draw(_dot, _tree[i], f);
			}
		return _dot;
	}
	template < class F, class G >
	friend
	Dotty &draw(Dotty &_dot,
	            const NSubTree_basic<n,T> &_tree,
		    const F &f, G g) {
		_dot.node( _tree.node, *_tree, g );
		for (size_t i = 0; i < n; i++)
			if ( _tree.exist(i) ) {
				_dot.edge( _tree.node,
					   _tree.node->soon[i], f(i) );
				draw(_dot, _tree[i], f);
			}
		return _dot;
	}
#endif /* _DOTTY_H_ */
};

template < size_t n, typename T, typename C, C &_cont >
class NTree_basic: public NSubTree_basic< n, T, C, _cont > {
public:
	NTree_basic(): NSubTree_basic< n, T, C, _cont >(new Node()) { };
	virtual ~NTree_basic() {
		if (node != NULL) node->_delete_chain_soon();
		delete node;
	}
};

#endif /* __NTREE_H */

