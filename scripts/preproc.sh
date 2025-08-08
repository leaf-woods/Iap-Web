#!/bin/bash

date;

###############################################################
### 20250808
### Given directory data which stores raw images data, 
### generate cloned directory data-S to store shrinked images.
###############################################################

#pwd
c_dir="/home/linye020603/iap-web/";
testRawData="data";
testImgData="data-S";

clone_dir_structure() {
    # clone directory structure using iap-web/data
    dirs=$(find $c_dir$testRawData -mindepth 1 -maxdepth 1 -type d | awk '{print $0}' | sed 's/data/data-S/g'); 
    echo $dirs;
    echo "Cloning directory structure";
    xargs mkdir -p <<< $dirs;
    echo "Directory structure cloned: $c_dir$testImgData";
}

if test -d $testImgData
then
    echo "Directory exists: $testImgData";
    if find $c_dir/$testImgData -mindepth 1 -maxdepth 1 | read; 
    then
        echo "Directory structure already cloned: $c_dir$testImgData";
    else
        clone_dir_structure;     
    fi
else
    mkdir $testImgData;
    clone_dir_structure;
fi

###############################################################
### 20250808
### Resize every JPG images under directory data and stored the
### shrinked images under data-S
###############################################################

found=$(find $c_dir$testRawData -type f -iname "*.JPG" -print -quit);
if [ -n $found ]
then
    echo "Images already shrinked.";
    exit;    
fi

fname="";
for fn in `find $c_dir$testRawData -type f -iname "*.JPG"`
do
    # convert -resize 1024 IMG_4348.JPG IMG_4348_S.JPG
    fname=$(echo $fn | sed 's/data/data-S/g' | sed 's/.JPG/_S.JPG/g');
    convert -resize 768 $fn $fname;
    echo "Converted: $fname";
done
