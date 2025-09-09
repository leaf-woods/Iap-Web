#!/bin/bash

date;

iap_cv_test_base=/home/linye020603/iap-web/cv-test;
dir_test_image_color=$iap_cv_test_base/image/color;
dir_test_util_convert=$iap_cv_test_base/util/convert;
dir_test_util_tree=$iap_cv_test_base/util/tree;

cd $dir_test_image_color && ./test_colordesc
cd $dir_test_util_convert && ./bgrhsvTest
cd $dir_test_util_tree/bstree && ./test
cd $dir_test_util_tree/htree && ./test
cd $dir_test_util_tree/vtree && ./test

cd $iap_cv_test_base