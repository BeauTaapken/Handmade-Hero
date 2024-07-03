#!/bin/sh

HANDMADE_BASE_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

export CommonCompilerFlags="-DHANDMADE_INTERNAL=1 -DHANDMADE_SLOW=1 -Werror -Wall -Wextra -Wpedantic \
	-Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wundef -fdiagnostics-show-option \
	-Wl,-Map=win32_handmade.map \
	-Wno-unused-parameter -Wno-unused-variable \
	-g -O3"
export CommonLinkerFlags="-lgdi32 -lwinmm"

mkdir -p ${HANDMADE_BASE_DIR}/build
pushd ${HANDMADE_BASE_DIR}/build
x86_64-w64-mingw32-gcc ${CommonCompilerFlags} ${HANDMADE_BASE_DIR}/code/win32_handmade.cpp -o handmade-windows ${CommonLinkerFlags}

# i686-w64-mingw32-gcc ${CommonCompilerFlags} ${HANDMADE_BASE_DIR}/code/win32_handmade.cpp -o handmade-windows ${CommonLinkerFlags}

popd

echo "Build done"
