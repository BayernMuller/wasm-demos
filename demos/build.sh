#!/bin/bash

set -e

if ! em++ -v 2>&1 | grep -q "Emscripten"; then
    echo "Emscripten is not installed"
    exit 1
fi

cd loop
em++ loop.cpp -o loop.js \
  -s MODULARIZE=1 \
  -s EXPORT_NAME=createModule \
  -s EXPORT_ES6=1 \
  -s EXPORTED_FUNCTIONS='["_pixelate", "_free", "_malloc"]' \
  -s EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' \
  -s ALLOW_MEMORY_GROWTH=1 \
  -s WASM=1 \
  -O3
cd ..



mv loop/*.js ../public
mv loop/*.wasm ../public