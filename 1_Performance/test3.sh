CILK_NWORKERS=4 taskset -c 0,3,6,9 ./sm out D &
CILK_NWORKERS=4 taskset -c 1,4,7,10 ./pqs 50000000 &
CILK_NWORKERS=4 taskset -c 2,5,8,11 ./ps 100000000
wait

