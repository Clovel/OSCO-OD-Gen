#!/bin/bash

MYDIR=$(dirname $(readlink -f $0))

mkdir -p $MYDIR/build/
cd $MYDIR/build/
cmake $MYDIR/generator
make
