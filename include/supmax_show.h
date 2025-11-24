#ifndef _SUPMAX_SHOW_H_
#define _SUPMAX_SHOW_H_

#include <ostream>
#include "seq_show.h"

#define SMF_LEDGE	1
#define SMF_COUNT	2
#define SMF_GROUP	4
#define SMF_SYMBOL	8
#define SMF_LIST	16

template <typename T, typename M, typename A>
class supmax_format {
public:
	typedef T			Type;
	typedef M			Map;
	typedef A			Alpha;
	typedef subseq_set_show<Map>	Show;
private:
	const int	_flag;
	const Map	&_map;
	const Alpha	&_alpha;
public:
	supmax_format(const Map &map, const Alpha &alpha, const int flag = 0 );
	supmax_format(const supmax_format &f );
	~supmax_format();

	void node(ostream &os, const Type a) const;
	void edge(ostream &os, const Type a,
                               const Type b, const size_t l) const;
};


#endif /* _SUPMAX_SHOW_H_ */

