#!/bin/bash
DATA=data.txt
RES=result.txt

while true
do
    if [ -s $DATA ]; then
        x=$(<$DATA)
        result=$(($x + 2 * $x))
        echo $result > $RES 
        break
    fi
done

while true
do
    LTIME=`stat -c %Z $DATA`
    while true    
    do
        ATIME=`stat -c %Z $DATA`

        if [[ "$ATIME" != "$LTIME" ]]
        then    
            x=$(<$DATA)
            result=$(($x + 2 * $x))
            echo $result > $RES
            LTIME=$ATIME
        fi
    done
done




