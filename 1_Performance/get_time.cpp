
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
 
int main(int argc, char *argv[])
{
   struct timespec stime, etime;
   double t;

   if (clock_gettime(CLOCK_MONOTONIC, &etime)) {
      fprintf(stderr, "clock_gettime failed");
      exit(-1);
   }


   t = etime.tv_sec + etime.tv_nsec / 1000000000.0;

   printf("%lf,", t);
 
   return 0;
}
