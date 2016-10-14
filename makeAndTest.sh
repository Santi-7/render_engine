#!/bin/bash

mkdir build
cd build
cmake ..
if make
then
    rayTracerTests/tests/Ray_Tracer_Tests_run
fi