# Challenge 1: Performance of Multiple Multicore Algorithms

## Setup:
Compile files, create ```out``` file (Input file for String Matching algorithm):
```sh
$ make
$ ./genchars 10000000000 >> out
```

## Run experiments:
```sh
$ ./run_test.sh
```

Output files have the format:
```sh
exp,stime,etime,cache-misses
test1,7835524.569812,7835542.300766,88937999
test2,7835542.358395,7835554.209689,71326049
test3,7835554.215591,7835569.668439,77183361
test4,7835569.672695,7835577.085204,70275192
...
```
Where:
- ```exp```: Name of the experiment test file (```test1```, ```test3```, ```test3```, ```test4```, ```test5```)
- ```stime```: Time at the start of the test (given by ```get_time.cpp```)
- ```etime```: Time at the end of the test (given by ```get_time.cpp```)
- ```cache-misses```: Number of cache-misses during the test (measured with perf)

The results used in the report are available [here](https://github.com/dmadariaga/multicore-programming-challenges/blob/master/1_Performance/results2017-07-02-08:46:25.data)
