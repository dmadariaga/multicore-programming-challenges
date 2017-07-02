CILK_NWORKERS=4 taskset -c 0-3 ./sm out D &
CILK_NWORKERS=4 taskset -c 4-7 ./pqs 50000000 &
CILK_NWORKERS=4 taskset -c 8-11 ./ps 100000000
wait
