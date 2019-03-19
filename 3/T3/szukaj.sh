#!/bin/bash

declare -i F
F=0
CHILD=

if [ "$#" -lt 2 ]; then
	echo "Not enough arguments!"
	exit -1
elif [ -d "$2" ]; then
    echo "'$2' is not a file!"
    exit -1
elif [ ! -d "$1" ]; then
		echo "'$1' is not a directory!"
		exit -1
fi

for item in $1/*; do
	if [ -d "$item" ]; then
		"$0" "$item" "$2" "$$" &
		CHILD+=("$!")
	elif [ -f "$item" ]; then
		if [ $(basename $item) == "$2" ]; then
			echo "File found: '$1/$2'"
			F=$((F + 1))
		fi
	fi
done

for i in "${CHILD[@]}"; do
	if [ "$i" ]; then
		wait "$i"
		F=$((F+$?))
	fi
done

if [ -z "$3" ]; then
	if [ "$F" -eq 0 ]; then
		echo "File not found!"
	else
		echo "Found files count: $F"
	fi
fi

exit "$F"