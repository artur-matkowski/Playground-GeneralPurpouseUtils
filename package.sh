#!/bin/bash


HIGH_NAME="high"
LOW_NAME="low"
BUILD_NAME="build"
HERE=${PWD##*/}

echo Modifier: $1
echo "Getting version for $HERE"


HIGH_NAME=`ssh debian@147.135.211.223 cat ./versions/$HERE-$HIGH_NAME`
LOW_NAME=`ssh debian@147.135.211.223 cat ./versions/$HERE-$LOW_NAME`
BUILD_NUMBER=`ssh debian@147.135.211.223 cat ./versions/$HERE-$BUILD_NAME`


let "BUILD_NUMBER++"


if [ "$1" = "stable" ]; then
	echo Incrementing stable build counter
	let "LOW_NAME++"
fi

VERIOSN_STRING="$HIGH_NAME.$LOW_NAME.$BUILD_NUMBER"

#ssh debian@147.135.211.223 bash -c "'echo $BUILD_NUMBER > ./versions/$HERE-$BUILD_NAME'"

echo $VERIOSN_STRING