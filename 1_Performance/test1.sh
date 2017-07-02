CILK_NWORKERS=4 ./string_matching out D &
CILK_NWORKERS=4 ./parallel_quick_sort 50000000 &
CILK_NWORKERS=4 ./prefix_sum 100000000
wait
