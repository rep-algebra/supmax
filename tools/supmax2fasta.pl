#!/usr/bin/perl

sub complexZIP {
        local $string = shift;

        $_ = `echo $string | gzip | wc -c` - 21;

        s/\n//g;

        return $_;
}

$i = 0;
while(<>) {
	s/\.//g;
	s/\n//g;
	s/.*N.*//g;
	($string, $count) = split(/:/);
	if (!($string eq "")) {
		$len = length($string);
		$cmpx = complexZIP($string);
		print "> Supermaximal $i -copy $count -len $len -cmpx $cmpx\n";
		print "$string\n";
	}
	$i++;
}
