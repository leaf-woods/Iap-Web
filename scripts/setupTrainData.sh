#!/bin/bash

# Uncomment each section to run the specific task.

test_dir="/home/linye020603/iap-web/train-data";
fname="";

###############################################
#
# Manually picked up 5 JPG from every month in 2024.
# Run this script to generate resized image with
# file name IMG_XXXX_S.JPG
# @20250810
# 
###############################################

#for fn in `find $test_dir -type f -iname "*.JPG"`
#do
#    fname=$(echo $fn | sed 's/.JPG/_S.JPG/g');
#    convert -resize 768 $fn $fname;
#    echo "converted: $fname";
#done


###############################################
#
# Round 1: Use quarter of every image to generate
# sky region with file name IMG_XXX_S_CR_R1.JPG
# @20250810
# 
###############################################

for fn in `find $test_dir -type f -iname "*_S.JPG"`
do
    fname=$(echo $fn | sed 's/_S.JPG/_S_CR_R1.JPG/g');
    convert $fn -crop 384x288+192+0 $fname;
    echo "cropped: $fname";
done
