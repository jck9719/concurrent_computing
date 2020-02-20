#!/bin/bash
echo $$
arg=$1
sleep 3
arg=$((arg + 1))
if [ $arg -lt 5 ]; then
./T3.sh $arg & ./T3.sh $arg &
fi
exit 0