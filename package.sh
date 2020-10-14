#!/bin/bash

HIGH_NAME="high"
LOW_NAME="low"
BUILD_NAME="build"
HERE=${PWD##*/}
ARCHITECTURE=`dpkg --print-architecture`
DISTRO=`lsb_release -a 2>/dev/null | grep Codename: | awk '{print $2}'`


PACKAGE="Package: $HERE"
PREFIX="\nVersion: "
SUFFIX="Section: custom
\nPriority: optional
\nArchitecture: $ARCHITECTURE
\nEssential: no
\nInstalled-Size: 1024
\nMaintainer: artur.matkowski.zan@gmail.com
\nHomepage: bitforge.pl
\nDescription: BitForge utilities support package (json, events, networked events (RPC), advanced logging"

echo Modifier: $1
echo "Getting version for $HERE"


HIGH_NAME=`ssh debian@147.135.211.223 cat ./versions/$HERE-$HIGH_NAME`
LOW_NAME=`ssh debian@147.135.211.223 cat ./versions/$HERE-$LOW_NAME`
BUILD_NUMBER=`ssh debian@147.135.211.223 cat ./versions/$HERE-$BUILD_NAME`


let "BUILD_NUMBER++"


#if [ "$1" = "stable" ]; then
	#echo Incrementing stable build counter
	#let "LOW_NAME++"
	#ssh debian@147.135.211.223 bash -c "'echo $LOW_NAME > ./versions/$HERE-$LOW_NAME'"
#fi

VERIOSN_STRING="$HIGH_NAME.$LOW_NAME.$BUILD_NUMBER"


#ssh debian@147.135.211.223 bash -c "'echo $BUILD_NUMBER > ./versions/$HERE-$BUILD_NAME'"


############## Creating package
mkdir package
mkdir package/DEBIAN


echo -e $PACKAGE$PREFIX$VERIOSN_STRING > package/DEBIAN/control
echo -e $SUFFIX >> package/DEBIAN/control
cat package/DEBIAN/control

mkdir package/usr
mkdir package/usr/lib
mkdir package/usr/lib/bitforge
cp build/rel/*.so package/usr/lib/bitforge/$HERE.so
dpkg-deb --build package
mkdir deb
mv package.deb deb/$HERE-"$VERIOSN_STRING"_$ARCHITECTURE.deb


############## Creating dev package
echo -e $PACKAGE-dev$PREFIX$VERIOSN_STRING > package/DEBIAN/control
echo -e $SUFFIX >> package/DEBIAN/control
echo "Depends: $HERE" >> package/DEBIAN/control
cat package/DEBIAN/control

rm -rf package/usr/lib
mkdir package/usr/include
mkdir package/usr/include/bitforge
mkdir package/usr/include/bitforge/utils
cp inc/* package/usr/include/bitforge/utils/
dpkg-deb --build package
mv package.deb deb/$HERE-"$VERIOSN_STRING"_$ARCHITECTURE-dev.deb


############## Creating dev-dbg package
echo -e $PACKAGE-dev-dbg$PREFIX$VERIOSN_STRING > package/DEBIAN/control
echo -e $SUFFIX >> package/DEBIAN/control
echo "Depends: $HERE-dev" >> package/DEBIAN/control
cat package/DEBIAN/control

mkdir package/usr/lib
mkdir package/usr/lib/bitforge
cp build/dbg/*.so package/usr/lib/bitforge/$HERE-dbg.so
dpkg-deb --build package
mv package.deb deb/$HERE-"$VERIOSN_STRING"_$ARCHITECTURE-dev-dbg.deb




scp deb/$HERE-"$VERIOSN_STRING"_$ARCHITECTURE.deb debian@147.135.211.223:/var/www/html/repo/$1/$HERE-"$VERIOSN_STRING"_$ARCHITECTURE.deb
scp deb/$HERE-"$VERIOSN_STRING"_$ARCHITECTURE-dev.deb debian@147.135.211.223:/var/www/html/repo/$1/$HERE-"$VERIOSN_STRING"_$ARCHITECTURE-dev.deb
scp deb/$HERE-"$VERIOSN_STRING"_$ARCHITECTURE-dev-dbg.deb debian@147.135.211.223:/var/www/html/repo/$1/$HERE-"$VERIOSN_STRING"_$ARCHITECTURE-dev-dbg.deb
ssh debian@147.135.211.223 "cd /var/www/html/repo/$1 && dpkg-scanpackages . /dev/null > Packages"

rm -rf package