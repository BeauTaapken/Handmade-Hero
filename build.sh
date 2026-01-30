#!/bin/sh

HANDMADE_BASE_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
DEF_DIR="${HANDMADE_BASE_DIR}/defs"

# TODO: Last line is for debug items only, please don't move and remove before final release"
export CommonCompilerFlags="-DHANDMADE_INTERNAL=1 -DHANDMADE_SLOW=1 -DHANDMADE_WIN32=1 -Werror -Wall -Wextra -Wpedantic \
	-Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op \
	-Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo \
	-Wstrict-null-sentinel -Wstrict-overflow=5 -Wundef -fdiagnostics-show-option -Wformat-security -Wzero-as-null-pointer-constant \
	-Wfloat-equal -fstrict-aliasing -Wduplicated-branches -fno-strict-aliasing \
	-Wno-unused-parameter -Wno-unused-variable \
	-g -ggdb -O3"
export CommonLinkerFlags="-lgdi32 -lwinmm"

mkdir -p ${HANDMADE_BASE_DIR}/build
pushd ${HANDMADE_BASE_DIR}/build

# 32 bit
i686-w64-mingw32-g++ ${CommonCompilerFlags} ${HANDMADE_BASE_DIR}/code/win32_handmade.cpp -o handmade-windows32 -Wl,-Map=win32_handmade32.map ${CommonLinkerFlags}

# 64 bit
x86_64-w64-mingw32-g++ ${CommonCompilerFlags} ${HANDMADE_BASE_DIR}/code/handmade.cpp ${DEF_DIR}/handmade.def -shared -o handmade.dll -Wl,-Map=handmade.map
x86_64-w64-mingw32-g++ ${CommonCompilerFlags} ${HANDMADE_BASE_DIR}/code/win32_handmade.cpp -o handmade-windows -Wl,-Map=win32_handmade.map ${CommonLinkerFlags}

popd

echo "Build done"
