getgrades
======

Dependencies
---
 - WWW::Mechanize [[debian](https://packages.debian.org/de/sid/libwww-mechanize-perl)] [[arch linux](https://www.archlinux.org/packages/community/any/perl-www-mechanize/)] [[cpan](http://search.cpan.org/~ether/WWW-Mechanize-1.74/lib/WWW/Mechanize.pm)]
 - HTML::TableExtract [[debian](https://packages.debian.org/de/wheezy/libhtml-tableextract-perl)] [[arch linux](https://www.archlinux.org/packages/community/any/perl-html-tableextract/)]  [[cpan](http://search.cpan.org/~msisk/HTML-TableExtract/lib/HTML/TableExtract.pm)]
 - `notify-send` should produce a message on your system (you can test this with `notify-send "test"`)

Installation
---
Add `getgrades` and `hsrmgradeformatter` to your `$PATH` and make it executable.
Example (you need root privileges for this one):
```
# wget https://raw.githubusercontent.com/jnboehm/getgrades/master/getgrades.pl -O /usr/local/bin/getgrades;
# wget https://raw.githubusercontent.com/jnboehm/getgrades/master/hsrmformatter.c -O /tmp/hsrmformatter.c;
# wget https://raw.githubusercontent.com/jnboehm/getgrades/master/hsrmformatter.h -O /tmp/hsrmformatter.h;
# chmod +x /usr/local/bin/getgrades;
# gcc -o /usr/local/bin/hsrmgradeformatter /tmp/hsrmgradeformatter.c
```
You still need to create your config file before you can make a lookup.

When all of this works you can install `notify-new-grades.sh` and `grade-daemon` with the following commands:

```
# wget https://raw.githubusercontent.com/jnboehm/getgrades/master/notify-new-grades.sh -O /usr/local/bin/notify-new-grades.sh;
# wget https://raw.githubusercontent.com/jnboehm/getgrades/master/grade-daemon.sh -O /usr/local/bin/grade-daemon;
# chmod +x /usr/local/bin/{grade-daemon,notify-new-grades.sh};
```

Afterwards you can invoke grade-daemon with the command line and let it run
asynchronously with `grade-daemon &`. The default sleep period lasts 3 minutes
but you can supply your own period as the first argument to it (i. e.
`grade-daemon 300 &`, to check every 300 seconds).

Configuration
---

getgrades reads the file `~/.config/getgrades/config`. In this file you
need to specify your username and your password. Enter those without
quotation marks or any special character that doesn't belong to your
credentials.

Example:
```
user = myuser
passwd = mypassword
```

Usage
---
Just fire away with `getgrades` and you'll get all your grades formatted
in a table with some additional information.

Sample output:
```
.------+---------------------------+------+----------+------.
| Nr   | Modul                     | Note | Semester | CrPt |
|------+---------------------------+------+----------+------|
|  100 | Anzahl CP 1. Fachsemester |      |          | 30,0 |
|      |                           |      |          |      |
|  200 | Anzahl CP 1. & 2. Fachsem |      |          | 40,0 |
|      |                           |      |          |      |
|  300 | Anzahl CP 1. - 3. Fachsem |      |          | 40,0 |
|      |                           |      |          |      |
|  400 | Zulassung Bachelor-Arbeit |      |          | 40,0 |
|      |                           |      |          |      |
...
| 2210 | Lineare Algebra           |  5,0 |          |  5,0 |
| 2211 |   - Klausur               |  5,0 | SoSe 15  |  4,0 |
| 2212 |   - Seminar               |  5,0 | SoSe 15  |  1,0 |
|      |                           |      |          |      |
| 4110 | Automatentheorie und Form |      |          |  0,0 |
| 4111 |   - Klausur               |  5,0 | SoSe 15  |  4,0 |
|      |                           |      |          |      |
| 9003 | Durchschnittsnote Deutsch |  1,0 |          |  0,0 |
`------+---------------------------+------+----------+------´
```

Limits
---
As it is now this script only connects to the qis instance of the server
of the Hochschule RheinMain, University of Applied Sciences and checks
for the major computer science with a Bachelor's degree.
You can of course change the source code to fit your needs, but most of
it is hardwired so you'll need to edit the code itself.

Thanks
---
Thanks to [[@jens-na](https://github.com/jens-na)] for letting me steal some of his stuff from / get inspired by his
repository `studipget`.
