#!/bin/bash

date;

echo "Clean bstree, htree, vtree.";
cd ./bstree && make clean
cd ../htree && make clean
cd ../vtree && make clean

if [ "$1" == "clean" ]
then
    exit;   
fi

echo;
echo "making bstree";
cd ../bstree && make

echo;
echo "making hsvtree";
cd ../htree && make

echo;
echo "making colorvaluetree";
cd ../vtree && make

