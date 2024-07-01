#!/bin/sh

HANDMADE_BASE_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

mkdir -p ${HANDMADE_BASE_DIR}/build
pushd ${HANDMADE_BASE_DIR}/build
i686-w64-mingw32-gcc -DHANDMADE_INTERNAL=1 -DHANDMADE_SLOW=1 -Werror -Wall -Wextra -Wpedantic \
	-Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wundef -fdiagnostics-show-option \
	-g -O3 ${HANDMADE_BASE_DIR}/code/win32_handmade.cpp -o handmade-windows -lgdi32 \
	-Wl,-Map=win32_handmade.map \
	-Wno-unused-parameter -Wno-unused-variable
popd

echo "Build done"
