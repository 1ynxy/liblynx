#!/bin/bash

[[ -d build ]] || mkdir -p build

cd build

cmake ..

if [ ! -f ./Makefile ]; then
    echo Makefile not created correctly
    exit
fi

make

if [ ! -f ./liblynx ]; then
    echo "executable not built correctly"
    exit
fi

chmod u+x liblynx

cd ..

[[ -d release ]] || mkdir -p release

mv build/liblynx release/liblynx
