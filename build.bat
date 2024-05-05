mkdir -p ./build
pushd ./build
x86_64-w64-mingw32-gcc -g ../code/win32_handmade.cpp -o handmade-windows
popd