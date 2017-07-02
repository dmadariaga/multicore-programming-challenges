# Challenge 2: Histogram of an Image

## Setup:
Compile files, create ```/images``` directory with all the ```PPM``` images used in the experiments:
```sh
$ ./setup.sh
```

## Run experiments:
```sh
$ ./run_test.sh
```

Output files have the format:
```sh
threads,image_size,time,cache-misses
1,2048,0.081244,861497
2,2048,0.032907,881179
3,2048,0.025801,891281
4,2048,0.015023,937536
...
```
Where:
- ```threads```: Number of threads used in the test
- ```image_size```: Equal to ```N``` if the image has ```N```X```N``` pixels
- ```time```: Execution time of the test
- ```cache-misses```: Number of cache-misses during the test (measured with perf)

The results used in the report are available [here](https://github.com/dmadariaga/multicore-programming-challenges/blob/master/2_Histogram/results2017-07-01-12:40:44.data)
