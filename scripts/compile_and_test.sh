#!/bin/bash

g++ src/main.cpp src/util/logger.cpp src/io/filein.cpp -o build/blang
./build/blang examples/program.blang
