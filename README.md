getgrades
======

Dependencies
---
 - WWW::Mechanize [[debian](https://packages.debian.org/de/sid/libwww-mechanize-perl)] [[arch linux](https://www.archlinux.org/packages/community/any/perl-www-mechanize/)] [[cpan](http://search.cpan.org/~ether/WWW-Mechanize-1.74/lib/WWW/Mechanize.pm)]
 - HTML::TableExtract [[debian](https://packages.debian.org/de/wheezy/libhtml-tableextract-perl)] [[arch linux](https://www.archlinux.org/packages/community/any/perl-html-tableextract/)]  [[cpan](http://search.cpan.org/~msisk/HTML-TableExtract/lib/HTML/TableExtract.pm)] 

Installation
---
Add `getgrades` and `hsrmgradeformatter` to your `$PATH` and make it executable.
Example (you need root powers for this one):
```
# wget https://raw.githubusercontent.com/ -O /usr/local/bin/getgrades;
# wget https://raw.githubusercontent.com/ -O /tmp/format-output.c;
# chmod +x /usr/local/bin/getgrades;
# gcc -o /usr/local/bin/hsrmgradeformatter /tmp/hsrmgradeformatter.c
```
You still need to create your config file before you can make a lookup.

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

Thanks
---
Thanks to @jens-na for letting me steal some of his stuff / get inspired by his `studipget`.
