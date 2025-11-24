#ifndef _SUPMAX_SHOW_CC_
#define _SUPMAX_SHOW_CC_

template <typename T, typename M, typename A>
supmax_format<T,M,A>::supmax_format(const Map &map,
                             const Alpha &alpha, const int flag = 0 )
: _flag(((flag && SMF_LIST)? flag | SMF_SYMBOL | SMF_GROUP: flag) |
	((flag && SMF_COUNT)? flag | SMF_SYMBOL | SMF_GROUP: flag) |
	((flag && SMF_SYMBOL)? flag | SMF_GROUP: flag)),
	_map(map), _alpha(alpha)
{ }

template <typename T, typename M, typename A>
supmax_format<T,M,A>::supmax_format(const supmax_format &f )
: _flag(f._flag), _map(f._map), _alpha(f._alpha)
{ };

template <typename T, typename M, typename A>
supmax_format<T,M,A>::~supmax_format()
{ };

template <typename T, typename M, typename A>
void 
supmax_format<T,M,A>::node(ostream &os, const Type a) const {
	if (_flag != 0 && _flag != SMF_LEDGE) {
		os << "node" << a;
		os << " [ label=\"";
		if (_flag & SMF_GROUP) {
		os << "{";
		for (size_t i = 0; i < a->data.alpha_size(); i++) {
			if (a->data.org != NULL && a->data.org[i].size() > 0) {
			if (i > 0) os << "}|{";
			os << "<" << i << ">";
			if (_flag & SMF_SYMBOL)
				os << _alpha(i) << ' ';
				if (_flag & SMF_COUNT) {
				if (a->data.org == NULL)
					os << "(0)";
				else
					os << "(" 
					   << a->data.org[i].size() << ")";
				}
				if (_flag & SMF_LIST) {
				if (a->data.org == NULL)
					os << "(0)";
				else
					os << "\\l" << Show(
					   a->data.org[i],_map,"nll","[,]");
				}
			}
		}
		os << "}";
		} else if (_flag & SMF_COUNT)
			os << "(" << a->data.size() << ")";
		os << "\"";
		if (_flag & SMF_GROUP)
			os << " shape=record";
		if (a->data.org == NULL)
			os << " color=red";
		os << " ]" << endl;
	}
};

template <typename T, typename M, typename A>
void
supmax_format<T,M,A>::edge(ostream &os, const Type a,
                    const Type b, const size_t l) const {
	os << "node" << a;
	// if (_flag & SMF_GROUP)
	// 	os << ":\"" << l << "\"";
	os << " -> node" << b;
	if (_flag & SMF_LEDGE)
		os << " [ label=\"" << _alpha(l) << "\" ]";
	os << endl;
};

#endif /* _SUPMAX_SHOW_CC_ */

