#!/bin/bash

os=`uname  -a`

mac="Darwin"
ubuntu="ubuntu"
centos="centos"

build_dir=""

if [[ $os =~ $mac ]];then
    echo "build in mac"
    build_dir=mac_build
else
  echo "build in $os"
  build_dir=linux_build
fi

rm -rf $build_dir
rm -rf ./build
rm -rf release

mkdir -p $build_dir
ln -s ./$build_dir build
cd $build_dir

cmake ..
make -j8

cd ../
if [[ $build_dir =~ linux_build ]];then
    sudo chown root release/linux/Debug/MediaServer
    sudo chmod u+s release/linux/Debug/MediaServer
fi
