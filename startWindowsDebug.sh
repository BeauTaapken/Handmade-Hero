#!/bin/sh

HANDMADE_BASE_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

pushd ${HANDMADE_BASE_DIR}/data
winedbg --gdb ${HANDMADE_BASE_DIR}/build/handmade-windows.exe
popd

