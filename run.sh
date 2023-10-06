#!/bin/bash

mkdir -p build

cd build

cmake ..

if [[ $? -ne 0 ]]; then
  echo "cmake не сработал"
  exit 1
fi

make

if [[ $? -ne 0 ]]; then
  echo "make не сработал"
  exit 1
fi

make install

if [[ $? -ne 0 ]]; then
  echo "проблемы с перелоцированием исполняющего файла PacmanGame"
fi

cd ..

rm -rf build

./DinoGame