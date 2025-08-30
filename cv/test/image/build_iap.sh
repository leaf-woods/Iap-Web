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

iap_cv_base=/home/linye020603/iap-web/cv;
iap_github_base=/home/linye020603/github-local/Iap-Web/cv;

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
    rsync $dry_run -av $iap_cv_base/image/color/imagecolordesc.h $iap_github_base/image/color/imagecolordesc.h
    rsync $dry_run -av $iap_cv_base/image/color/imagecolordesc.cpp $iap_github_base/image/color/imagecolordesc.cpp
    rsync $dry_run -av $iap_cv_base/util/convert/convert_bgrhsv.h $iap_github_base/util/convert/convert_bgrhsv.h
    rsync $dry_run -av $iap_cv_base/util/convert/convert_bgrhsv.cpp $iap_github_base/util/convert/convert_bgrhsv.cpp
    rsync $dry_run -av $iap_cv_base/util/convert/convert_bgrhsv_test.cpp $iap_github_base/util/convert/convert_bgrhsv_test.cpp  
    rsync $dry_run -av $iap_cv_base/util/tree/htree/*.h $iap_github_base/util/tree/htree/
    rsync $dry_run -av $iap_cv_base/util/tree/htree/*.cpp $iap_github_base/util/tree/htree/
fi

echo;

if [ $DRY_RUN == 0 ]
then
    echo "Cleaning iap-web cv";
    make clean
    echo;
    echo "Make iap-web cv and run test";
    make #&& ./runtest
fi
