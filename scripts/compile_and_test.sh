#!/bin/bash

g++ src/main.cpp src/util/logger.cpp src/io/file_in.cpp -o build/blang
./build/blang examples/program.blang
