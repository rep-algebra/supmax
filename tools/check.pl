#!/usr/bin/perl

if (int @ARGV != 3) {
	print "Usar:\n";
	print "./check.pl {secuencia} {supermaximales} {cobertura}\n";
	exit (0);
}

open(SEC, "< " . $ARGV[0]);
open(SECS, "< " . $ARGV[1]);
$coverture = $ARGV[2];

$seq = "";

print "Secuencia mayor:", $ARGV[0] , "\n";
print "Supermaximales:", $ARGV[1] , "\n";
print "Cobertura:", $coverture , "\n";

print "\nLeyendo secuencia mayor\n";
while(<SEC>) {
	s/\n//g;
	s/^>.*$//g;
	$seq .= $_;
}

$stat_no = 0;
$stat_more = 0;
$stat_less = 0;
$stat_equ = 0;
$cant = 0;

print "Leyendo supermaximales y comparando\n";
while(<SECS>) {
	s/\n//g;
	($sequence, $count, $set) = split(/:/); # Supermaximal, Cantidad encontrada, Posicion en el conjunto de secuencias #
	$i = 0; # Posicion donde se encuenctra el supermaximal en la secuencia mayor #
	$c = 0; # Cantidad de veces que se repite el maximal en la secuencia mayor #
	%pos = {};
	while( ($i = index $seq, $sequence, $i) != -1 ) {
		# $pos{$c} = $i;
		$i++;
		$c++;
	}
	$x = int($count / int $coverture); # Valor esperado de repeticiones en la secuencia mayor #
	#print $sequence, ":", $x, ":", $c, ":";
	if ($c < 2) { $stat_no++; } # Lo esperado no es repetición #
	if ($x < $c) { $stat_more++; } # Lo esperado es menor a lo que realmente existe #
	if ($x > $c) { $stat_less++; } # Lo esperado es mayor a lo que realmente existe #
	if ($x == $c) { $stat_equ++; } # Lo esperado es igual a lo que realmente existe #
	#foreach $c (keys %pos) {
	#	print $pos{$c}, ",";
	#}
	#print "\n";
	$cant++;
	#print $cant, "\r";
}

print "\n\n";
print "Cantidad de supermaximales predichos: $cant \n";
print "Cantidad de no es supermaximales: $stat_no \n";
print "Repeticiones con prediccion menor al real: $stat_more \n";
print "Repeticiones con prediccion mayor al real: $stat_less \n";
print "Repeticiones con prediccion igual al real: $stat_equ \n";
print "\n";

