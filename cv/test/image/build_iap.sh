#!/bin/bash

date;
echo "Build iap-web cv";

iap_cv_base=/home/linye020603/iap-web/cv;
iap_dev_base=/home/linye020603/iap-web;

echo "Sync files.";

# Sync package util/tree
rsync -av $iap_dev_base/util/example1/bstree/ITreeNode.h $iap_cv_base/util/tree/ITreeNode.h
rsync -av $iap_dev_base/util/example1/bstree/ibstree.h $iap_cv_base/util/tree/ibstree.h
rsync -av $iap_dev_base/util/example1/bstree/bstree.h $iap_cv_base/util/tree/bstree/bstree.h
rsync -av $iap_dev_base/util/example1/bstree/bstree.cpp $iap_cv_base/util/tree/bstree/bstree.cpp
rsync -av $iap_dev_base/util/example1/bstree/bstreeTest.cpp $iap_cv_base/util/tree/bstree/bstreeTest.cpp

rsync -av $iap_dev_base/util/example1/htree/*.h $iap_cv_base/util/tree/htree/
rsync -av $iap_dev_base/util/example1/htree/*.cpp $iap_cv_base/util/tree/htree/

rsync -av $iap_dev_base/util/example1/vtree/*.h $iap_cv_base/util/tree/vtree/
rsync -av $iap_dev_base/util/example1/vtree/*.cpp $iap_cv_base/util/tree/vtree/

# Sync package util/print
rsync -av $iap_dev_base/util/example1/iap_print.h $iap_cv_base/util/print/iap_print.h
rsync -av $iap_dev_base/util/example1/iap_print.cpp $iap_cv_base/util/print/iap_print.cpp

# Sync package util/convert
rsync -av $iap_dev_base/util/example1/convert_number.h $iap_cv_base/util/convert/convert_number.h
rsync -av $iap_dev_base/util/example1/convert_number.cpp $iap_cv_base/util/print/convert_number.cpp
rsync -av $iap_dev_base/util/example4/convert_bgrhsv.h $iap_cv_base/util/convert/convert_bgrhsv.h
rsync -av $iap_dev_base/util/example4/convert_bgrhsv.cpp $iap_cv_base/util/convert/convert_bgrhsv.cpp
rsync -av $iap_dev_base/util/example4/convert_bgrhsv_test.cpp $iap_cv_base/util/convert/convert_bgrhsv_test.cpp

# Sync package context is already in production

# Sync package image
rsync -av $iap_dev_base/util/example1/imagecolordesc.h $iap_cv_base/image/color/imagecolordesc.h
rsync -av $iap_dev_base/util/example1/imagecolordesc.cpp $iap_cv_base/image/color/imagecolordesc.cpp

echo;
echo "Cleaning iap-web cv";
make clean

echo;
echo "Make iap-web cv and run test";
make && ./runtest