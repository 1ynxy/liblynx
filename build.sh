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

# https://jichu4n.com/posts/how-x-window-managers-work-and-how-to-write-one-part-i/
# https://www.x.org/releases/X11R7.7/doc/libxcb/tutorial/index.html#intro
# https://vulkan-tutorial.com/Drawing_a_triangle/Presentation/Window_surface
# https://harrylovescode.gitbooks.io/vulkan-api/content/chap03/chap03.html