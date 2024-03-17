#!/bin/sh

set -xe

CFLAGS="-Wall -Wextra -ggdb `pkg-config --cflags raylib`"
LIBS="`pkg-config --libs raylib` `pkg-config --libs glfw3` -lm -ldl -lpthread"

mkdir -p ./build/

if [ -z "$1" ]; then
    echo "Building in release mode"
    clang $CFLAGS -o ./build/fourier ./src/main.c ./src/wave.c $LIBS -L./build/ -I./include/
    exit 0
fi

if [ "$1" = "debug" ]; then
    echo "Building in debug mode"
    clang $CFLAGS -o ./build/fourier ./src/main.c ./src/wave.c $LIBS -L./build/ -I./include/ -DDEBUG
    exit 0
fi
