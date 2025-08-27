#!/bin/bash

date;
echo "Build iap-web cv on local github repository.";
echo;

DRY_RUN="";
if [ "$1" == "--dry-run" ]
then
    DRY_RUN="--dry-run";
    echo "Use rsync dry run. Will not copy files.";
    echo;
fi

iap_cv_base=/home/linye020603/iap-web/cv;
iap_github_base=/home/linye020603/github-local/Iap-Web/cv;

echo "Sync files.";

rsync $DRY_RUN -av $iap_cv_base/ $iap_github_base
echo;
echo "Cleaning iap-web cv";
make clean

echo;
echo "Make iap-web cv and run test";
make #&& ./runtest