#!/bin/bash

HIGH_NAME="high"
LOW_NAME="low"
BUILD_NAME="build"
HERE=${PWD##*/}

PREFIX="Package: linuxconfig
\nVersion: "
SUFFIX="Section: custom
\nPriority: optional
\nArchitecture: armhf
\nEssential: no
\nInstalled-Size: 1024
\nMaintainer: bitforge.pl
\nDescription: test package"

echo Modifier: $1
echo "Getting version for $HERE"


HIGH_NAME=`ssh debian@147.135.211.223 cat ./versions/$HERE-$HIGH_NAME`
LOW_NAME=`ssh debian@147.135.211.223 cat ./versions/$HERE-$LOW_NAME`
BUILD_NUMBER=`ssh debian@147.135.211.223 cat ./versions/$HERE-$BUILD_NAME`


let "BUILD_NUMBER++"


if [ "$1" = "stable" ]; then
	echo Incrementing stable build counter
	let "LOW_NAME++"
	ssh debian@147.135.211.223 bash -c "'echo $LOW_NAME > ./versions/$HERE-$LOW_NAME'"
fi

VERIOSN_STRING="$HIGH_NAME.$LOW_NAME.$BUILD_NUMBER"

ssh debian@147.135.211.223 bash -c "'echo $BUILD_NUMBER > ./versions/$HERE-$BUILD_NAME'"


############## Creating package
mkdir package
mkdir package/DEBIAN

echo -e $PREFIX$VERIOSN_STRING > package/DEBIAN/control
echo -e $SUFFIX >> package/DEBIAN/control
cat package/DEBIAN/control

mkdir package/usr
mkdir package/usr/lib
cp build/rel/*.so package/usr/lib/$HERE.so
dpkg-deb --build package
mkdir deb
mv package.deb deb/$HERE-"$VERIOSN_STRING"_armhf.deb

scp deb/$HERE-"$VERIOSN_STRING"_armhf.deb debian@147.135.211.223:/var/www/html/debian/$1/$HERE-"$VERIOSN_STRING"_armhf.deb

rm -rf package deb