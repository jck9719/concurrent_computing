#!/bin/bash
while true; do
    
            LTIME=`stat -c %Z data.txt`
            while true; do
                ATIME=`stat -c %Z data.txt`
                if [[ "$ATIME" != "$LTIME" ]]
                    then    
                        data=$(cat data.txt)
                        result=$(( $data * 3 - 6 ))
                        echo -n $result > results.txt
                        LTIME=$ATIME
                fi
            done
    
done

