#ifndef __DEBUG_H
#define __DEBUG_H

#include <iostream>

extern int __debug;

#define DEBUG(L,P,F,M) if (__debug && L) \
	cerr << P << ":" << F << ":" << M << endl;

void set_debug(int _d);

#endif

