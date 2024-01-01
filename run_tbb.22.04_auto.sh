docker run -ti --rm \
    --cpuset-cpus="0-$1" \
    --name my-running-app-2204 \
    -v $PWD:/usr/src/myapp \
    cpp-experiment:22.04 \
    /bin/bash -c "cd /usr/src/myapp/build && \
        cmake .. && \
        make -j$num_cores && \
        ./main"

echo ""
echo We used 0 to $1 cores 

# if not using cmake, do 
# /bin/bash -c 'g++ -std=c++20 -O3 main.cpp -DPARALLEL -ltbb -o main && ./main' # working (compile success)
