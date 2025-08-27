#!/bin/bash

# From dev to cv on localhost. See $iap_cv_base and $iap_deb_base.
date;
echo "Build iap-web cv on development repo.";

# https://stackoverflow.com/questions/13276788/create-array-in-bash-dynamically
src=();
dest=();

DRY_RUN="";
if [ "$1" == "--dry-run" ]
then
    DRY_RUN="--dry-run";
    echo "Use rsync dry run. Will not copy files.";
fi

iap_cv_base=/home/linye020603/iap-web/cv;
iap_dev_base=/home/linye020603/iap-web;

compare_mtime() {
    # We don't check existence here.
    # $1: Source file
    # $2: Destination file
    echo "Compare $1 and $2";
    if [ $1 -ot $2 ]
    then
        echo "$1 is outdated.";
        return -1;
    fi
    return 1;
}

# Check package util/tree
echo;
echo "Check package util/tree";
for fn in `find $iap_dev_base/util/example1/bstree $iap_dev_base/util/example1/htree $iap_dev_base/util/example1/vtree -type f -name "*.cpp" -o -name "*.h"`
do
    if [[ $fn == *"ibs"* ]] || [[ $fn == *"ITree"* ]]
    then
        #echo "Super: $fn";
        dfn=$(echo $fn | sed 's/util\/example1\/bstree/cv\/util\/tree/g');
    else
        # substitute $iap_dev_base/util/example1 to $iap_cv_base/util/tree
        dfn=$(echo $fn | sed 's/util\/example1/cv\/util\/tree/g');
        #echo $dfn;
    fi 
   
    compare_mtime $fn $dfn;
    #stat $fn | grep "Modify:" ;
    #stat $dfn | grep "Modify:";
    #echo;
    if [ $? == -1 ]
    then
        echo "Package util/tree dev outdated. Cannot build.";
        exit;
    fi
    src+=("$fn");
    dest+=("$dfn");
done
echo "Check package util/tree OK.";
echo;

# Check package util/print
echo "Check package util/print";
if [ $iap_dev_base/util/example1/iap_print.h -ot $iap_cv_base/util/print/iap_print.h ] || [ $iap_dev_base/util/example1/iap_print.cpp -ot $iap_cv_base/util/print/iap_print.cpp ]
then
    echo "Package util/print dev outdated. Cannot build.";
    exit;
fi
src+=("$iap_dev_base/util/example1/iap_print.h");
dest+=("$iap_cv_base/util/print/iap_print.h");
src+=("$iap_dev_base/util/example1/iap_print.cpp");
dest+=("$iap_cv_base/util/print/iap_print.cpp");
echo "Check package util/print OK.";
echo;

# Check package util/convert
echo "Check package util/convert";
for fn in `find $iap_dev_base/util/example1 $iap_dev_base/util/example4 -type f -name "convert*.cpp" -o -name "convert*.h"`
do
    dfn=$(echo $fn | sed -E 's/util\/example[1,4]/cv\/util\/convert/g');

    compare_mtime $fn $dfn;
    #stat $fn | grep "Modify:" ;
    #stat $dfn | grep "Modify:";
    #echo;
    if [ $? == -1 ]
    then
        echo "Package util/convert dev outdated. Cannot build.";
        exit;
    fi
    src+=("$fn");
    dest+=("$dfn");
done
echo "Check package util/convert OK.";
echo;

# Check package image/color
echo "Check package image/color";
if [ $iap_dev_base/util/example1/imagecolordesc.h -ot $iap_cv_base/image/color/imagecolordesc.h ] || [ $iap_dev_base/util/example1/imagecolordesc.cpp -ot $iap_cv_base/image/color/imagecolordesc.cpp ]
then
    echo "Package image/color dev outdated. Cannot build.";
    exit;
fi
src+=("$iap_dev_base/util/example1/imagecolordesc.h");
dest+=("$iap_cv_base/image/color/imagecolordesc.h");
src+=("$iap_dev_base/util/example1/imagecolordesc.cpp");
dest+=("$iap_cv_base/image/color/imagecolordesc.cpp");
echo "Check package image/color OK.";
echo;

echo "Sync files.";
if [ ${#src[@]} != ${#dest[@]} ] 
then
    echo "Error occurred. Cannot build.";
fi

length=${#src[@]}
for (( i=0; i<${length}; i++ ));
do
  #echo "index: $i, value: ${src[$i]}";
  rsync $DRY_RUN -av ${src[$i]} ${dest[$i]}; 
done

echo;
echo "Cleaning iap-web cv";
make clean

echo;
echo "Make iap-web cv and run test";
make #&& ./runtest