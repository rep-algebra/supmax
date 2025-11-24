#ifndef _DOTTY_2_H_
#define _DOTTY_2_H_

#include <string>
#include <iostream>

#define DIGRAPH	"digraph"
#define TO	"->"
#define ENDL	";\n"
#define SATRIB	"[ "
#define EATRIB	" ]"

template <class T>
struct Dotty_Identity {
	const T &operator[](const T &a) const { return a; }
};

template < class T >
class Dotty_Node {
	Dotty_Node(const T &node) { };
	Dotty_Node &color(const string &clr) const;
	Dotty_Node &fontcolor(const string &clr) const;
	Dotty_Node &fontname(const string &clr) const;
	Dotty_Node &fontsize(const double &clr) const;
	Dotty_Node &height(const double &clr) const;
	Dotty_Node &width(const double &clr) const;
	Dotty_Node &label(const string& t) const;
	Dotty_Node &layer(const string& t) const;
	Dotty_Node &shape(const string &ds) const;
	Dotty_Node &shapefile(const string &) const;
	Dotty_Node &style(const string &) const;
};

template < class Tnode, class Tedge,
	   class Mnode = Dotty_Identity<Tnode>,
	   class Medge = Dotty_Identity<Tedge> >
class Dotty {
private:
	ostream &_os;
	map < string, string > &attribs;
public:
	Dotty(ostream &os, string name): _os(os) {
		_os << "digraph " << name << " {" << endl;
	}
	~Dotty() {
		_os << "}" << endl;
	}
	node(const Tnode &n) {
		_os << n << SATRIB << "label = " << EATRIB << ENDL;
	}
	edge(const Tnode &a, const Tnode &b, const Tedge &e) {
		_os << a << TO << b << SATRIB << e << EATRIB << ENDL;
	}
};

/*
 * Dotty d(cout);
 * d.node(1, attrib().label("pepe"));
 * /

#endif /* _DOTTY_2_H_ */

