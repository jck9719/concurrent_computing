#!/bin/bash
DATA=data.txt
RES=result.txt

x=0

if [ -s $RES ]; then
    x=1
fi

read number
echo $number > $DATA


while true
do
    if [ $x -eq 1 ]; then
        break
    fi

    if [[ ( $x -eq 0 ) && ( -s $RES) ]]; then
        x=$(<$RES)
        echo $x
        exit 0
    fi
done

while true
do
    if [ -s $RES ]; then
        LTIME=`stat -c %Z $RES`
        while true    
        do
            ATIME=`stat -c %Z $RES`

            if [[ "$ATIME" != "$LTIME" ]]
            then    
                x=$(<$RES)
                echo $x
                exit 0
            fi

        done
    fi
done