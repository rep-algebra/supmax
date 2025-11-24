#!/usr/bin/perl

$c = 1.5;
$rsize = 5;
$rerror = 2;

sub ale {
	($min, $max) = @_;
	$v = ($max - $min) * rand();
	return int ($min + $v);
}

while(<>) {
	s/\n//g;
	if (/^>\s*((\w|\s|\|)+).*$/) {
		$name = $1;
	} else {
		s/\s//g;
		s/a/A/g; s/c/C/g; s/t/T/g; s/g/G/g;
		$sequence = $sequence . $_;
	}
}

$total = length($sequence) * $c;

print "Sequence name: $name\n";
print "Sequence size: " . length($sequence) . "pb\n";
print "Sequence:\n$sequence\n";
print "Reading coverage: " . $c . "\n";
print "Expected base read: " . $total . "\n";
print "Read size: " . $rsize . "+-" . $rerror . "\n";

$id = 0;
while($total > 0) {
	$begin = ale(0, length($sequence));
	$len = ale($rsize - $rerror, $rsize + $rerror);
	print ">id$id\n";
	print substr($sequence, $begin, $len)."\n";
	$total = $total - $len;
	$id++;
	for ($i = 0; $i < $len; $i++) {
		$coverage{$begin + $i}++;
	}
}

open(OUTPUT, "> coverage");

$s = 0;
for ($i = 0; $i < length($sequence); $i++) {
	print OUTPUT "$i " . $coverage{$i} . "\n";
	$s = $s + $coverage{$i};
}

$p = $s / length($sequence);
print OUTPUT "# Coverage: $p\n";

