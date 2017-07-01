// g++ -std=c++11 -o phs parallel_radix_sort.cpp -fcilkplus -lcilkrts -lrt
// C++ program for implementation of Heap Sort
#include <iostream>
#include <limits.h>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include <cilk/common.h>
using namespace std;
 
static void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

static void radix_sort(int *from, int *to, unsigned bit) {
  if (!bit || to < from + 1) return;
 
  int *ll = from, *rr = to - 1;
  for (;;) {
    /* find left most with bit, and right most without bit, swap */
    while (ll < rr && !(*ll & bit)) ll++;
    while (ll < rr &&  (*rr & bit)) rr--;
    if (ll >= rr) break;
      swap(ll, rr);
  }

  if (!(bit & *ll) && ll < to) ll++;
  bit >>= 1;
 
  cilk_spawn radix_sort(from, ll, bit);
  radix_sort(ll, to, bit);
}
 
int *generate_array(int n, int alphabet) {
  srand(256);
  int *x = (int *)malloc(n*sizeof(int));
  
  for (int i = 0; i < n; i++)
    x[i] = rand() % alphabet;

  return x;
}

void print_array(int *x, int n) {
  printf("Array : ");
  for (int i = 0; i < n; i++)
    printf("%u ", x[i]);
  printf("\n");
}

int main(int argc, char* argv[]) {

  if(argc != 3) {
    fprintf(stderr, "Usage: %s <number of elements> <alphabet size>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  int n = atoi(argv[1]);
  int alphabet = atoi(argv[2]);
  int *x = generate_array(n, alphabet);
  
  struct timespec stime, etime;
  double t;
  
  if (clock_gettime(CLOCK_THREAD_CPUTIME_ID , &stime)) {
    fprintf(stderr, "clock_gettime failed");
    exit(-1);
  }
  radix_sort( x, x + n, INT_MIN );

  if (clock_gettime(CLOCK_THREAD_CPUTIME_ID , &etime)) {
    fprintf(stderr, "clock_gettime failed");
    exit(-1);
  }
  
  t = (etime.tv_sec - stime.tv_sec) + (etime.tv_nsec - stime.tv_nsec) / 1000000000.0;

  //elapsed time
  printf("%lf\n", t););
  
  return EXIT_SUCCESS;
}