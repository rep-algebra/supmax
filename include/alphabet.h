#ifndef __ALPHABET_H
#define __ALPHABET_H

#include <stdexcept>
#include <string.h>

typedef char	symbol;
typedef symbol*	symbol_list;
typedef size_t	symbol_id;

class invalid_symbol: public std::range_error {
private:
	symbol s;
public:
	explicit invalid_symbol(symbol);

	virtual const char* what() const throw();
};

class invalid_symbol_id: public std::range_error {
private:
	symbol_id s;
public:
	explicit invalid_symbol_id(symbol_id);

	virtual const char* what() const throw();
};

template < symbol_list A, symbol_id n >
class alphabet {
public:
	alphabet() {};
	
	symbol_id size() const { return n; };

	symbol_id operator()(symbol s) const
	{ symbol *S = (symbol *)memchr(A,s,n);
	  if (S == NULL) throw invalid_symbol(s);
	  // assert(S != NULL);
	  return (S - A); };

	symbol    operator()(symbol_id s) const
	{ if (s >= n) throw invalid_symbol_id(s);
	  // assert(s < n);
	  return (A[s]); };
};

#endif /* __ALPHABET_H */

