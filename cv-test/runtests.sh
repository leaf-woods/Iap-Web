#!/bin/bash

date;

iap_ghl_test_cv_base=/home/linye020603/github-local/Iap-Web/cv-test;
dir_test_image=$iap_ghl_test_cv_base/image;
dir_test_util=$iap_ghl_test_cv_base/util;

cd $dir_test_image/color && ./test_colordesc
cd $dir_test_image/color/compare && ./testComparator
cd $dir_test_image/region && ./testRegion
cd $dir_test_util/convert && ./bgrhsvTest
cd $dir_test_util/convert && ./testConvertnumber
cd $dir_test_util/log && ./testLog
cd $dir_test_util/tree/bstree && ./test
cd $dir_test_util/tree/htree && ./test
cd $dir_test_util/tree/vtree && ./test

cd $iap_ghl_test_cv_base

# test_init_train