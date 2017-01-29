#!/bin/bash
if [ "$1" != "" ]; then
    it=$1
else
    it=10
fi

make clean
make

for i in $(seq "$it")
do
   	echo "Iteration $i"
   	make run
done