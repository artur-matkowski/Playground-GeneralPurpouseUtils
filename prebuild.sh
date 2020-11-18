#!/bin/bash
cd $(dirname $0)
ARCHITECTURE=`dpkg --print-architecture`

mkdir -p Logs 

mkdir -p build 
mkdir -p build/$ARCHITECTURE
mkdir -p build/$ARCHITECTURE/rel
mkdir -p build/$ARCHITECTURE/rel/obj
mkdir -p build/$ARCHITECTURE/dbg
mkdir -p build/$ARCHITECTURE/dbg/obj

