#!/bin/bash

date;

iap_ghl_cv_example_base=/home/linye020603/github-local/Iap-Web/examples
iap_ghl_cv_test_base=/home/linye020603/github-local/Iap-Web/cv-test;
dir_test_image=$iap_ghl_cv_test_base/image;
dir_test_stat=$iap_ghl_cv_test_base/statistics;
dir_test_util=$iap_ghl_cv_test_base/util;

cd $iap_ghl_cv_example_base/example8 && ./test
cd $dir_test_image/color && ./test_colordesc
cd $dir_test_image/color/compare && ./testComparator
cd $dir_test_image/color/datatype && ./testSubMatr
cd $dir_test_image/color/datatype && ./testMatrixBounds
cd $dir_test_image/region && ./testRegion
cd $dir_test_image/region/context && ./testRegionContext
cd $dir_test_image/region/datatype && ./testBorderPixelDiffNode
cd $dir_test_image/region/explore && ./testRegionExplore
cd $dir_test_image/train && ./test_init_train
cd $dir_test_image/train && ./testFactSkyInitTrain
cd $dir_test_image/train/policies && ./testBorders
cd $dir_test_image/train/policies && ./testCloud
cd $dir_test_stat && ./testGetStddev
cd $dir_test_util/convert && ./bgrhsvTest
cd $dir_test_util/convert && ./testConvertnumber
cd $dir_test_util/log && ./testLog
cd $dir_test_util/tree/bstree && ./test
cd $dir_test_util/tree/dtree && ./test
cd $dir_test_util/tree/htree && ./test
cd $dir_test_util/tree/vtree && ./test

cd $iap_ghl_cv_test_base

# test_init_train