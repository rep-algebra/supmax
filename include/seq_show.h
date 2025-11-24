#ifndef _SEQ_SHOW_H_
#define _SEQ_SHOW_H_

#include "config.h"
#include <ostream>
#include <ctype.h>
#include "seq.h"

template < typename C >
class subseq_show {
private:
	const subseq &_ss;
	const C &_c;
	const char *_sep;
public:
	subseq_show (const subseq &ss, const C &c, const char *sep = "<,>"):
		_ss(ss), _c(c), _sep(sep) { };

#ifdef _PREV_
	friend ostream &operator<<(ostream &os, const subseq_show &sd) {
		os << "Don't support on _SEQ_ mode" << endl;
		return os;
	}
#else
	friend ostream &operator<<(ostream &os, const subseq_show &sd) {
		if (isalpha(sd._sep[0])) {
			if (sd._sep[0] != 'n')
			os << "\\" << sd._sep[0];
		} else {
			os << sd._sep[0];
		}
		os << sd._c.find(sd._ss.sequence)->second;
		if (isalpha(sd._sep[1])) {
			if (sd._sep[1] != 'n')
			os << "\\" << sd._sep[1];
		} else {
			os << sd._sep[1];
		}
		os << sd._ss.pbegin();
		if (isalpha(sd._sep[1])) {
			if (sd._sep[1] != 'n')
			os << "\\" << sd._sep[1];
		} else {
			os << sd._sep[1];
		}
		os << sd._ss.pend();
		if (isalpha(sd._sep[2])) {
			if (sd._sep[2] != 'n')
			os << "\\" << sd._sep[2];
		} else {
			os << sd._sep[2];
		}
		return os;
	}
#endif
};

template < typename C >
class subseq_set_show {
private:
	const subseq_set &_ss;
	const C &_c;
	const char *_sep;
	const char *_sep_i;
public:
	subseq_set_show(const subseq_set &ss, const C &c,
			const char *sep = "{,}", const char *sep_i = "<,>"):
		_ss(ss), _c(c), _sep(sep), _sep_i(sep_i) { };

	friend ostream &operator<<(ostream &os, const subseq_set_show &sd) {
		if (isalpha(sd._sep[0])) {
			if (sd._sep[0] != 'n')
			os << "\\" << sd._sep[0];
		} else {
			os << sd._sep[0];
		}
		for(subseq_set::const_iterator i = sd._ss.begin();
		    i != sd._ss.end(); i++) {
			if (i != sd._ss.begin())
			if (isalpha(sd._sep[1])) {
				if (sd._sep[1] != 'n')
				os << "\\" << sd._sep[1];
			} else {
				os << sd._sep[1];
			}
			os << subseq_show<C>(*i, sd._c, sd._sep_i);
		}
		if (isalpha(sd._sep[2])) {
			if (sd._sep[2] != 'n')
			os << "\\" << sd._sep[2];
		} else {
			os << sd._sep[2];
		}
		return os;
	}
};

#endif /* _SEQ_SHOW_H_ */

