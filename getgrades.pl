#!/usr/bin/perl

use strict;
use WWW::Mechanize;
use Getopt::Std;
use feature qw(say);
use HTML::TableExtract;

my ($user, $pass) = load_cfg();
my $url = 'https://qis.hs-rm.de/qisserver/rds?state=user&type=0';
my $client = WWW::Mechanize->new(autocheck => 1);
my $te = HTML::TableExtract->new(slice_columns => 0 , headers => [qw(Semester Termin Note Status Vermerk)] );
my @links;

sub load_cfg {
  my $user = undef;
  my $pass = undef;

  open(FILE_H, "$ENV{HOME}/.config/getgrades/config") || die("Can't open ~/.config/getgrades/config.\n");
  while (<FILE_H>) {
    chomp $_;
    (my $key,my $value) = split("=", $_);
    $value =~ s/^\s+|\s+$//g; # trim whitespace
    $key =~ s/^\s+|\s+$//g;

    if($key eq "user") { $user = $value; }
    if($key eq "passwd") { $pass = $value; }
  }
  return ($user, $pass);
}

# This is the authentication for the login, for some reason the fields
# have silly names but they have to be matched.
$client->get($url);
my $response = $client->submit_form(
    form_number => 1,
    fields => {
        asdf => $user, 
        fdsa => $pass,
    }
    );

# $client->follow_link( text => 'Prüfungsverwaltung' );
# cannot read the Umlaut so you have to rely on alternative ways to find
# the link, e.g. through a regular expression

# $client->follow_link( n => 9 );
# is an alternative but I find it too unreliable
$client->follow_link( text_regex => qr/(?i:fungsverwaltung)/ );

$client->follow_link( text => 'Notenspiegel (NUR ZUR INFO!!!)' );

$client->follow_link( text => 'Abschluss Bachelor' );

$client->follow_link( text_regex => qr/Angewandte Informatik /i );

# now you're on the site and parsing the interesting content--your grades.
$te->parse( $client->content );

my $ts;
my $row;
my @te = $te->tables;
my $line;
# parse the wanted table and stuff everything into one long string.
# Also mark the end of the module for easier formatting
foreach $row ($te[0]->rows) {
    $line .= "@$row";
    $line .= "ENDOFMODULE";
}

# call a compiled program to take care of the formatting, it gets the
# string passed as one string
exec "/usr/local/bin/hsrmgradeformatter \'$line\'";
