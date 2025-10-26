#!/bin/bash

date;

if [ $# != 2 ] 
then
    echo "Error. Expected number of arguments: 2";
    echo "Num of arguments:$#";
    exit;
fi

OBJS_ARG1=$1;
#"commons/fact_sky_train/sky_init_train.o commons/fact_sky_train/fact_sky_init_train.o commons/fact_sky_train/iapcv_env.o commons/fact_sky_train/iap_print.o";

OBJS_ARG2=$2;
#"commons/context/matrix_bounds.o commons/context/region_builder.o commons/context/region_colors_provider.o commons/context/region_explore.o commons/context/region_evaluator.o commons/context/region_print.o commons/context/pixel_comparator.o commons/context/get_stddev.o commons/context/explore_helper.o commons/context/simple_explore.o commons/context/abstract_explore.o commons/context/iapcv_log.o commons/context/iap_print.o";

#echo "ARG1: $1";
#echo;
#echo "ARG2: $2";
#echo;

leng_arg1=${#OBJS_ARG1};
leng_arg2=${#OBJS_ARG2};

OBJS="";
SHORTER="";
LONGER="";
if [ $leng_arg1 -gt $leng_arg2 ] 
then
    LONGER=$OBJS_ARG1;
    SHORTER=$OBJS_ARG2;
else
    LONGER=$OBJS_ARG2;
    SHORTER=$OBJS_ARG1;
fi

#echo "SHORTER: $SHORTER";
#echo "LONGER: $LONGER";

OBJS=$LONGER;
#echo "OBJS set: $OBJS";

#https://stackoverflow.com/questions/10586153/how-to-split-a-string-into-an-array-in-bash
readarray smaller_arr <<< "$SHORTER";

#echo "Size: ${#smaller_arr[@]}";

for element in "${smaller_arr[@]}"
do
    #echo "Procdssing: $element";
    obj=${element##*\/};

    leng=${#obj};
    last=${obj:$length-1};
    if [[  "$last" != "o"  ]] 
    then
        # We assume it is a new line char.
        obj=${obj:0:$length-1};
    fi

    if [[ $LONGER == *"$obj"* ]];
    then
        echo "Found: $obj";
    else
        OBJS="${OBJS} $element";
    fi
done

echo;
echo "OBJS: $OBJS";


