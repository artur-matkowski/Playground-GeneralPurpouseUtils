#!/bin/bash

HERE=${PWD##*/}
ARCHITECTURE=`dpkg --print-architecture`
DISTRO=`lsb_release -a 2>/dev/null | grep Codename: | awk '{print $2}'`

cp build/$ARCHITECTURE/rel/*.so /usr/lib/lib$HERE.so
cp inc/* /usr/include/bitforge/utils/