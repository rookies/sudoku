#!/bin/bash
cd $(dirname $0)
g++ -std=c++11 -o sudoku-solve src/*.cpp
