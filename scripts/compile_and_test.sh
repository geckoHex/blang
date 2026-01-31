#!/bin/bash

g++ src/main.cpp src/util/logger.cpp -o build/blang
./build/blang examples/program.blang
