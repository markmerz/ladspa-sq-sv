#!/usr/bin/perl

use strict;
use warnings;
use Math::Trig;
use PDL::DSP::Windows;

# helper for calculating hilbert transformer coefficents

# my $N = 801;
my $N = 2000;

my @coefs = ();
my $win = new PDL::DSP::Windows($N, 'hamming');
my $windata = $win->get_samples;

my @window = ();
foreach my $sample ($windata->dog) {
	push @window, $sample;
}

for (my $i = 0; $i < $N / 4; $i++) {
 	$coefs[($N / 2) + (2 * $i - 1)] = +2 / (pi * (2 * $i - 1));
 	$coefs[($N / 2) - (2 * $i - 1)] = -2 / (pi * (2 * $i - 1));
}

my $count = 1;
for (my $c = 0; $c < $N; $c++) {
	if (defined $coefs[$c]) {
		my $res = -1 * $coefs[$c] * $window[$c];
		print $res . "f, ";
		if ($count++ % 5 == 0) {
			print "\n";
		}
	}
}


