# Challenge 3: Comparison of Parallel Sorting Algorithms

## Setup:
Compile files:
```sh
$ make
```

## Run experiments:
```sh
$ ./run_test.sh
```

Output files have the format:
```sh
algorithm,threads,n,alphabet,time,cache-misses
pqs,1,10000,256,0.002052,12079
pms,1,10000,256,0.001259,15147
pcs,1,10000,256,0.001203,9570
prs,1,10000,256,0.001579,13260
...

```
Where:
- ```algorithm```: Parallel sorting algorithm used. ```pqs``` for QuickSort, ```pms``` for MergeSort, ```pcs``` for CountingSort and ```prs``` for RadixSort
- ```threads```: Number of threads used in the test
- ```n```: Length for the array to sort
- ```alphabet```: Size of the alphabet used (Numbers are in the interval [0, ```alphabet```-1])
- ```time```: Execution time of the test
- ```cache-misses```: Number of cache-misses during the test (measured with perf)

The results used in the report are available [here](https://github.com/dmadariaga/multicore-programming-challenges/blob/master/3_Sorting/results2017-07-01-17:58:14.data)
