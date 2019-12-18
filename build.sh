#!/bin/bash

rm -rf linux_build
rm -rf ./build
rm -rf release
mkdir -p linux_build
ln -s ./linux_build build
cd linux_build

cmake ..
make -j8

cd ../
sudo chown root release/linux/Debug/MediaServer
sudo chmod u+s release/linux/Debug/MediaServer
