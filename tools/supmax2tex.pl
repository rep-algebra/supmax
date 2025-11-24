#!/usr/bin/perl

print "\\begin{center}\n";
print "\\begin{itemize}\n";
while(<>) {
	s/\.//g;
	s/\n//g;
	($string, $count) = split(/:/);
	print '\\item ', $string, ', ', $count, "\n";
}
print "\\end{itemize}\n";
print "\\end{center}\n";
