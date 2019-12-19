#!/bin/bash
git submodule init
git submodule update

sudo apt-get install cmake
sudo apt-get install libx264-dev
sudo apt-get install libfaac-dev
sudo apt-get install libmp4v2-dev
sudo apt-get install libhiredis-dev
#sudo apt-get install libsdl-dev
#sudo apt-get install libavcodec-dev
#sudo apt-get install libavutil-dev

mkdir -p linux_build
rm -rf ./build
ln -s ./linux_build build
cd linux_build

cmake ..
make -j4
