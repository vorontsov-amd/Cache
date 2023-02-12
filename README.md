# LFU Cache
2 my implementations of the LFU cache with O(1) algorithmic complexity. There is also an implementation of an ideal cache that knows the future, to compare the speed of work and the number of cache hits.

## Requirements 

The following applications have to be installed:

1. CMake 3.2 version (or higher)
2. GTest
3. g++


## Compiling 

To compile each of the cache you need to use сmake in the directory build:

``` cmd
$ mkdir build
$ cd build
$ сmake ..
$ make all
```

## Run the program:

You can find all binaries in dir build/bin


LFU cache: 
``` cmd
$ ./bin/lfuCache
```
Perfect cache:

``` cmd
$ ./bin/perfectCache
```

Test for cache:

``` cmd
$ ./bin/testCache
```

## Useful materials:
* http://dhruvbird.com/lfu.pdf - **An O(1) algorithm for implementing the LFU
cache eviction scheme**
