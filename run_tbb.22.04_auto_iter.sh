#!/bin/bash

# 0부터 k까지 반복
for i in {0..19}
do
    echo "Running with 0 to $i cores"
    ./run_tbb.22.04_auto.sh $i
    echo ""
done
