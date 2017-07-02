CILK_NWORKERS=4 taskset -c 0,3,6,9 ./string_matching out D &
CILK_NWORKERS=4 taskset -c 1,4,7,10 ./parallel_quick_sort 50000000 &
CILK_NWORKERS=4 taskset -c 2,5,8,11 ./prefix_sum 100000000
wait

