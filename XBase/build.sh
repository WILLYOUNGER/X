#!/bin/bash

bin_dir=./bin
build_dir=./build

echo "构建："

if [ ! -d "$bin_dir" ]; then
    echo "创建目录bin"
    mkdir -p $bin_dir
fi

if [ ! -d "$build_dir" ]; then
    echo "创建目录build"
    mkdir -p $build_dir
fi

if [ ! -d ./bin/log ]; then
    echo "创建日志目录bin/log"
    mkdir -p ./bin/log
fi

if [ ! -f ./bin/web.xml ];then
    echo "复制web.xml"
    cp ./src/XPublic/XFrames/XResourse/xml/web.xml ./bin/web.xml
fi;

if [ ! -d ./bin/root ];then
    echo "复制root目录"
    cp -r ./src/XPublic/XFrames/XServlet/XWebDefaultRoot ./bin/root
fi;

cd ./build
cmake ..

echo "编译："

cd ../bin
make 

cd ../
