#!/bin/bash

date;
echo "Build iap-web cv on local github repository.";
echo;

### --dry-run
### --manually

SYNC_MANUALLY=0;
DRY_RUN=0;

if [ "$1" == "--dry-run" ] || [ "$2" == "--dry-run" ]
then
    DRY_RUN=1;
    echo "Use rsync dry run. Will not copy files.";
    echo;
fi

if [ "$1" == "--manually" ] || [ "$2" == "--manually" ]
then
    SYNC_MANUALLY=1;
    echo "Sync files indivually.";
    echo;
fi

iap_dev_base=/home/linye020603/iap-web;
iap_cv_base=/home/linye020603/iap-web/cv;
iap_github_base=/home/linye020603/github-local/Iap-Web/cv;

# All makefiles under $iap_cv_test_base has to update manually one by one.
iap_cv_test_base=/home/linye020603/iap-web/cv-test;
iap_github_test_base=/home/linye020603/github-local/Iap-Web/cv-test;

if [ $SYNC_MANUALLY == 0 ]
then 
    echo "Sync files.";
    if [ $DRY_RUN == 0]
    then
        rsync -av $iap_cv_base/ $iap_github_base
    else
        rsync --dry-run -av $iap_cv_base/ $iap_github_base
    fi 
else
    dry_run="";
    if [ $DRY_RUN == 1 ]
    then
        dry_run="--dry-run";
    fi
    # https://github.com/leaf-woods/Iap-Web/commit/9c6ba60c31071cbed315b953a41c0b3155513b21
    #rsync $dry_run -av $iap_cv_base/image/color/imagecolordesc.h $iap_github_base/image/color/imagecolordesc.h
    #rsync $dry_run -av $iap_cv_base/image/color/imagecolordesc.cpp $iap_github_base/image/color/imagecolordesc.cpp
    #rsync $dry_run -av $iap_cv_base/image/color/imagecolorvalues.h $iap_github_base/image/color/imagecolorvalues.h
    #rsync $dry_run -av $iap_cv_base/image/color/imagecontext.h $iap_github_base/image/color/imagecontext.h
    #rsync $dry_run -av $iap_cv_base/image/color/imagereader.h $iap_github_base/image/color/imagereader.h
    #rsync $dry_run -av $iap_cv_base/image/color/imagereader.cpp $iap_github_base/image/color/imagereader.cpp

    #rsync $dry_run -av $iap_cv_base/image/color/compare/ $iap_github_base/image/color/compare

    #rsync $dry_run -av $iap_cv_base/image/color/datatype/status/status.h $iap_github_base/image/color/datatype/status/status.h
    
    #rsync $dry_run -av $iap_cv_base/image/color/ $iap_github_base/image/color
    
    #rsync $dry_run -av $iap_cv_base/image/region/region_builder.cpp $iap_github_base/image/region/region_builder.cpp

    #rsync $dry_run -av $iap_cv_base/image/region/ $iap_github_base/image/region

    #rsync $dry_run -av $iap_cv_base/image/toolbox/sky.h $iap_github_base/image/toolbox/sky.h
    #rsync $dry_run -av $iap_cv_base/image/toolbox/sky.cpp $iap_github_base/image/toolbox/sky.cpp

    #rsync $dry_run -av $iap_cv_base/manage/iclearable.h $iap_github_base/manage/iclearable.h

    #rsync $dry_run -av $iap_cv_base/util/convert/convertnumber.cpp $iap_github_base/util/convert/convertnumber.cpp
    #rsync $dry_run -av $iap_cv_base/util/convert/convert_bgrhsv.h $iap_github_base/util/convert/convert_bgrhsv.h
    #rsync $dry_run -av $iap_cv_base/util/convert/convert_bgrhsv.cpp $iap_github_base/util/convert/convert_bgrhsv.cpp
    #rsync $dry_run -av $iap_cv_base/util/convert/convert_bgrhsv_test.cpp $iap_github_base/util/convert/convert_bgrhsv_test.cpp  
    #rsync $dry_run -av $iap_cv_base/util/tree/ITreeNode.h $iap_github_base/util/tree/ITreeNode.h
    rsync $dry_run -av $iap_cv_base/util/tree/ibstree.h $iap_github_base/util/tree/ibstree.h
    #rsync $dry_run -av $iap_cv_base/util/tree/bstree/bstree.h $iap_github_base/util/tree/bstree/bstree.h
    #rsync $dry_run -av $iap_cv_base/util/tree/bstree/bstree.cpp $iap_github_base/util/tree/bstree/bstree.cpp
    rsync $dry_run -av $iap_cv_base/util/tree/htree/hsvtree.h $iap_github_base/util/tree/htree/hsvtree.h
    rsync $dry_run -av $iap_cv_base/util/tree/htree/hsvtree.cpp $iap_github_base/util/tree/htree/hsvtree.cpp
    #rsync $dry_run -av $iap_cv_base/util/tree/vtree/colorvaluetree.h $iap_github_base/util/tree/vtree/colorvaluetree.h
    rsync $dry_run -av $iap_cv_base/util/tree/vtree/colorvaluetree.cpp $iap_github_base/util/tree/vtree/colorvaluetree.cpp
    
    rsync $dry_run -av $iap_cv_base/util/print/ $iap_github_base/util/print

    rsync $dry_run -av $iap_cv_base/util/log/ $iap_github_base/util/log

    #rsync $dry_run -av $iap_cv_base/main.cpp $iap_github_base/main.cpp
    #rsync $dry_run -av $iap_cv_base/makefile $iap_github_base/makefile

    #rsync $dry_run -av $iap_dev_base/util/example6/*.cpp $iap_github_base/../examples/example6/
    #rsync $dry_run -av $iap_dev_base/util/example6/*.h $iap_github_base/../examples/example6/

    #rsync $dry_run -av $iap_dev_base/util/example8/*.* $iap_github_base/../examples/example8/
    
    ##### TEST PACKAGES: Manually run rsync only #####
    
    rsync $dry_run -av $iap_cv_test_base/util/tree/htree/hsvtreeTest.cpp $iap_github_test_base/util/tree/htree/hsvtreeTest.cpp

    #rsync $dry_run -av $iap_cv_test_base/ $iap_github_test_base
    
fi

echo;

#if [ $DRY_RUN == 0 ]
#then
#    echo "Cleaning iap-web cv";
#    make clean
#    echo;
#    echo "Make iap-web cv and run test";
#    make #&& ./runtest
#fi
