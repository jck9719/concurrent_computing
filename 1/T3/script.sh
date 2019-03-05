#!/bin/bash
arg=$1
echo $$
sleep 3
arg=$((arg + 1))
if [ $arg -lt 5 ]; then
./script.sh $arg & ./script.sh $arg &
fi
exit 0
