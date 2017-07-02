CILK_NWORKERS=4 taskset -c 0-3 ./string_matching out D &
CILK_NWORKERS=4 taskset -c 4-7 ./parallel_quick_sort 50000000 &
CILK_NWORKERS=4 taskset -c 8-11 ./prefix_sum 100000000
wait
