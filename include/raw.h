#ifndef _RAW_H_
#define _RAW_H_

#include "include/seqformat.h"
#include <sstream>

class raw: public seqformat_inputiterator {
private:
	static int id;
public:
	raw(istream &is): seqformat_inputiterator(is)
	{ }
	~raw()
	{ }

	bool next() {
		if (!is) return false;
		stringstream buffer;
		buffer << "id" << id;
		_name = buffer.str();
		is >> _sequence;
		id++;
		return (is);
	}
};

#endif
