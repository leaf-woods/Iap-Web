#!/bin/bash

# https://tldp.org/LDP/abs/html/comparison-ops.html

# https://www.cyberciti.biz/faq/unix-howto-read-line-by-line-from-file/
date;

start=$(grep -n 'Examples and TEST PACKAGES' build_iap.sh | awk -F  ":" '{print $1}');
echo "Found start line: $start";

input="build_iap.sh"
######################################
# $IFS removed to allow the trimming # 
#####################################
while read -r line
do
  if [[ $line == rsync* ]] && [[ $line != *.cpp ]] && [[ $line != *.h ]]
  then
      echo;
      echo "read line: $line";
      fn=${line##* };
      #echo "fn: $fn";
      fn=${fn#*/};
      #echo "trimmed fn: $fn";

      echo "Processing file: $fn";
      if [[ $fn == *makefile ]]
      then
          echo "makefile: $fn";
          sed -i -e 's/iap_cv_base/iap_ghl_cv_base/g' -e 's/iap-web/github-local\/Iap-Web/' $fn
      else
          if [ -d $fn ]; then
              for fm in `find $fn -type f -name "makefile"`
              do
                  echo "Found makefile: $fm";
                  sed -i -e 's/iap_cv_base/iap_ghl_cv_base/g' -e 's/iap-web/github-local\/Iap-Web/' $fm
              done
          else
              echo "Not a directory: $fn";
          fi
      fi
  fi
done < <(tail -n "+$start" "$input")
# https://askubuntu.com/questions/289160/how-to-read-file-starting-from-a-specific-number-of-line-within-the-while-read

echo "Processing file: ./makefile";
sed -i -e 's/iap_cv_example_base/iap_ghl_cv_example_base/g' -e 's/iap-web\/util/github-local\/Iap-Web\/examples/' makefile;
sed -i -e 's/iap_cv_base/iap_ghl_cv_base/g' -e 's/iap-web/github-local\/Iap-Web/' makefile;

echo "Processing file: ./runtests.sh";
sed -i -e 's/iap_cv_example_base/iap_ghl_cv_example_base/g' -e 's/iap-web\/util/github-local\/Iap-Web\/examples/' runtests.sh;
sed -i -e 's/iap_cv_test_base/iap_ghl_cv_test_base/g' -e 's/iap-web/github-local\/Iap-Web/' runtests.sh;

echo "Processing file: ../cv/makefile";
sed -i -e 's/iap_cv_base/iap_ghl_cv_base/g' -e 's/iap-web/github-local\/Iap-Web/' ../cv/makefile;