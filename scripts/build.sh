#!/usr/bin/env bash
SRCDIR=$(pwd)
cd $SRCDIR/../build && cmake -D CMAKE_BUILD_TYPE=Release $SRCDIR && make
cp $SRCDIR/run.sh $SRCDIR/../build/run.sh
