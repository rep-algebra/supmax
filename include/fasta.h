#ifndef _FASTA_H_
#define _FASTA_H_

#include "include/seqformat.h"
#include <regex.h>

#define MAXMATCH 20
#define RE_NAME "^>\\([[:alnum:]]\\+\\)[[:space:]]*\\([[:space:]]\\+[[:alnum:]]\\+=[[:alnum:]]\\+\\)*[[:space:]]*$"
#define RE_SEQ  "[ACTGN]+"

class fasta: public seqformat_inputiterator {
private:
	regex_t re_name;
	regex_t re_seq;
	string _n;
	regmatch_t match[MAXMATCH];
	char strerror[100];

	bool is_header(const char *str) {
		int r = regexec(&re_name, str, MAXMATCH, match, 0);
		return r == 0;
	}
public:
	fasta(istream &is): seqformat_inputiterator(is)
	{ int r;
	  r = regcomp(&re_name, RE_NAME, 0);
	  if (r != 0) {
		regerror(r, &re_name, strerror, 100);
		cout << strerror << endl;
	  } 
	  r = regcomp(&re_seq, RE_SEQ, 0);
	  if (r != 0) {
		regerror(r, &re_name, strerror, 100);
		cout << strerror << endl;
	  } 
	}
	~fasta()
	{ }

	bool next() {
		char line[256];
		_sequence = string();

		if (!is) return false;
		while (is) {
			is.getline(line, 256);

			if (strlen(line) > 0 && is_header(line)) {
				if (_n.size() > 0) {
					_name = _n;
					_n = string(line,
						match[1].rm_so, match[1].rm_eo);
					return true;
				} else {
					_n = string(line,
						match[1].rm_so, match[1].rm_eo);
				}
			} else {
				for(size_t i = 0; i < strlen(line); i++) {
				char c = toupper(line[i]);
				switch (c) {
				case 'A':
				case 'C':
				case 'T':
				case 'G':
				case 'N':
					_sequence += c;
					break;
				default:
					break;
				} }
			}
		}
		if (_n.size() > 0) {
			_name = _n;
			return true;
		}
		return true;
	}
};

#endif
