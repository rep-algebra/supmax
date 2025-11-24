#!/usr/bin/perl

print "\\begin{center}\n";
print "\\begin{itemize}\n";
while(<>) {
	s/\.//g;
	print '\item ', $_;
}
print "\\end{itemize}\n";
print "\\end{center}\n";
