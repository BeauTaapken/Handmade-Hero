#!/bin/sh

HANDMADE_BASE_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

mkdir -p ${HANDMADE_BASE_DIR}/build
pushd ${HANDMADE_BASE_DIR}/build
x86_64-w64-mingw32-gcc -DHANDMADE_INTERNAL=1 -DHANDMADE_SLOW=1 -Wall -g ${HANDMADE_BASE_DIR}/code/win32_handmade.cpp -o handmade-windows -lgdi32
popd

echo "Build done"
