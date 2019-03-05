#!/bin/bash
read input
echo -n $input > data.txt

LTIME=`stat -c %Z results.txt`
while true ; do
   ATIME=`stat -c %Z results.txt`
   if [[ "$ATIME" != "$LTIME" ]]
        then    
            res=$(cat results.txt)
            echo $res
            exit 0
   fi
done
