mkdir -p ./build
pushd ./build
x86_64-w64-mingw32-gcc -DHANDMADE_INTERNAL=1 -DHANDMADE_SLOW=1 -Wall -g ../code/win32_handmade.cpp -o handmade-windows -lgdi32
popd

echo "Build done"
