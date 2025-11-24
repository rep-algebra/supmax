#ifndef _SEQFORMAT_H_
#define _SEQFORMAT_H_

#include <iostream>
#include <map>
#include <string>

using namespace std;

class seqformat {
protected:
	string _name;
	string _sequence;
	map<string,string> _properties;
public:
	seqformat() {}
	~seqformat() {}

	const string &seq() const
	{ return _sequence; };
	const string &name() const
	{ return _name; };
	const string &property(const string &p) const
	{ return (_properties.find(p))->second; };

	string &seq()
	{ return _sequence; };
	string &name()
	{ return _name; };
	string &property(const string &p)
	{ return _properties[p]; };
};

class seqformat_inputiterator: public seqformat {
protected:
	istream &is;
public:
	seqformat_inputiterator(istream &_is): is(_is)
	{ }
	virtual ~seqformat_inputiterator()
	{ }

	virtual bool next() = 0;

	bool operator++() { return next(); }
};

#endif /* _SEQFORMAT_H_ */
