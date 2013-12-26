#!/bin/sh

set -x

aclocal -I m4
libtoolize
autoconf
automake --add-missing --copy