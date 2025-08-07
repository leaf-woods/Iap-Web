#!/bin/bash

# Without 20201119/, 20201120/ 2023/

echo "iphone 6 images";

echo "Changing IFS.";
OIFS="$IFS";
IFS=$'\n';

# 20240522 Fix bugs described in "20240521 MySql import scripts bugs"
DEBUG=1;

# 20250807 Switched to Chromebook
test_dir="/home/linye020603/iap-web/data/2024-11";

echo "Use Test Directory: $test_dir";
echo;

fname='';
rpath='';
extension='';
p_date='';
p_time='';
category='';

print_entry() {
    echo "RPath: $rpath FName: $fname Extension: $extension Date: $p_date Time: $p_time Category: $category";
}

# 20250807 If iphone no need to use find
for fn in `find $test_dir -type f -iname "*.JPG" -o -iname "*.PNG"`
do
    fname=${fn##*\/};
    length=$((${#fn} - ${#fname})); 
    rpath=${fn:0:$length};
    extension=${fname##*.};
    length=$((${#fname} - ${#extension}));
    length=$((length-1));
    fname=${fname:0:$length};

    # 20250807 Images on iphone only: Use extension to determine category
    # Image meta data date and time specific to iphone images.
    if [ "$extension" == "PNG" ]
    then
        category="SC";
        dt=$(identify -format '%[date:modify]\n' $fn);
        p_date=`date -d $dt +%F`; 
        p_time=`date -d $dt +%T`; 
    else
        if [ "$extension" == "JPG" ]
        then
            category="CM";
            dt=$(identify -format '%[exif:datetime]\n' $fn);
            p_time=${dt##* }; 
            length=$((${#dt} - ${#p_time})); 
            p_date=${dt:0:$length}; 
            p_date=${p_date//[:]/-};
        else 
            category="NA";
        fi
    fi
    
    if [ $DEBUG == 1 ]
    then 
        print_entry;
    fi
done
IFS="$OFIS";
echo "RESET IFS.";    
    
