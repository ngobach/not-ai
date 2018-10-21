#!/usr/bin/env bash

SRCDIR=$(pwd)
for lf in libopencv_core libopencv_highgui libopencv_imgcodecs libopencv_imgproc; do
	ln -sf ${lf}.so.3.4.3 $SRCDIR/opencv/lib/${lf}.so
	ln -sf ${lf}.so.3.4.3 $SRCDIR/opencv/lib/${lf}.so.3.4
	ln -sf ${lf}.so.3.4.3 $SRCDIR/opencv/lib/${lf}.so.3
done

# Building
cd $SRCDIR/../build
cmake -D CMAKE_BUILD_TYPE=Release $SRCDIR &> /dev/null
make &> /dev/null
cp $SRCDIR/run.sh $SRCDIR/../build/run.sh

