#!/bin/sh

mkdir libs
mkdir -p tmp/generated
git clone https://github.com/vlm/asn1c.git
cd asn1c
test -f configure || autoreconf -iv
./configure
make && sudo make install
cd ..
cd tmp/generated
asn1c ../../data/rocket.asn -D . -gen-autotools -fcompound-names
autoreconf --force --install
autoconf -i
./configure --prefix=$(pwd)/../../libs/
make && make install
cd ../..
make clean
make