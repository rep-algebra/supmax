bin_PROGRAMS = supmax
supmax_SOURCES = alphabet.cc debug.cc  clo.cc main.cc  seq.cc
supmax_LDADD = 
INCLUDES = -I../include
CXXFLAGS = -ggdb -g3 -Wall -fexceptions -O0
#CXXFLAGS = -Wall -fexceptions -O3

clo.cc: ../templates/options.xml
	clo++ --output c++ $<
	mv clo.cxx clo.cc
	mv clo.h ../include
