#!/bin/sh

CFLAGS="-Wall -Wextra -ggdb `pkg-config --cflags raylib`"
LIBS="`pkg-config --libs raylib` `pkg-config --libs glfw3` -lm -ldl -lpthread"

if [ "$1" != "clean" ] && [ -n "$1" ]; then
    echo "Usage: ./build.sh [clean]"
    exit 1
fi

if [ -z "$1" ]; then
    mkdir -p ./bin/
    echo "Build Completed."
    clang $CFLAGS -o ./bin/fourier ./src/main.c ./src/wave.c $LIBS -L./bin/ -I./include/
    exit 0
fi

if [ "$1" = "clean" ]; then
    rm -r ./bin/
    echo "Clean completed."
    exit 0
fi
