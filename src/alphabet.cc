#include <stdio.h>
#include "include/alphabet.h"

#define MSG_SIZE 256
char _alpha_message_[MSG_SIZE];

invalid_symbol::invalid_symbol(symbol _s): range_error("Invalid symbol"), s(_s) { };

const char*
invalid_symbol::what() const throw() {
	snprintf(_alpha_message_, MSG_SIZE, "%s '%c'", range_error::what(), s);

	return _alpha_message_;
}

invalid_symbol_id::invalid_symbol_id(symbol_id _s): range_error("Invalid symbol id"), s(_s) { };

const char*
invalid_symbol_id::what() const throw() {
	snprintf(_alpha_message_, MSG_SIZE, "%s #%c", range_error::what(), s);

	return _alpha_message_;
}

