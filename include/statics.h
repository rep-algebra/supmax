#ifndef __STATICS_H
#define __STATICS_H

#include "ntree.h"

class statics {
public:
	size_t maximal;
	size_t supermaximal;
	size_t nodes;

	statics(): maximal(0), supermaximal(0), nodes(0) {};
	void newnode() { nodes++; }
	void newsupermaximal() { supermaximal++; }
	void newmaximal() { maximal++; }
};

#endif /* __STATICS_H */

