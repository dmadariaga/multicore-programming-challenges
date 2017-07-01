// Compile: gcc -std=gnu99 -o histogram_par histogram_par.c -fcilkplus -lcilkrts

#include <stdio.h>
#include <stdlib.h>

#include <sys/time.h>
#include <time.h>
#include <ctype.h>

#ifdef NOPARALLEL
#define __cilkrts_get_nworkers() 1
#define cilk_for for
#define cilk_spawn 
#define cilk_sync 
#else
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include <cilk/common.h>
#endif

#define num_threads __cilkrts_get_nworkers()

#define uchar unsigned char

void error(char const *message){
    fprintf(stderr, "Error: %s\n", message);
    exit(1);
}
void readPPMHeader(FILE *fp, int *width, int *height){
    char ch;
    int  maxval;

    if (fscanf(fp, "P%c\n", &ch) != 1 || ch != '3')
      error("file is not in ppm format (P3)");

    /* skip comments */
    ch = getc(fp);
    while (ch == '#'){
      do {
      ch = getc(fp);
        } while (ch != '\n'); /* read to the end of the line */
        ch = getc(fp);            
    }

    if (!isdigit(ch)) error("cannot read header information from ppm file");

    ungetc(ch, fp);   /* put that digit back */

    /* read the width, height, and maximum value for a pixel */
    fscanf(fp, "%d\n%d\n%d\n", width, height, &maxval);

    if (maxval != 255) error("image is not true-color (24 bit); read failed");
}

void uploadImage(uchar *image, int size, uchar *imageR, uchar *imageG, uchar *imageB){
  for (int i=0; i<size; i+=3){
    int index = (int)i/3;
    imageR[index] = image[i];
    imageG[index] = image[i+1];
    imageB[index] = image[i+2]; 
  }
}

void histogram(uchar *A, uint size, uint *H){
  uint chk = size/num_threads;
  uint *temp_H[num_threads];
  cilk_for(uint i = 0; i < num_threads; i++) {
    uint  ll = i*chk, ul = ll + chk;
    if(i == num_threads-1)
      ul = size;

    temp_H[i] = calloc(sizeof(uint), 256);
    for(uint j = ll; j < ul; j++) {
      temp_H[i][A[j]] ++;
    }
  }

  for (uint i = 0; i < num_threads; i++) {
    for (uint j = 0; j < 256; j++){
      H[j] += temp_H[i][j];
    }
  }
}

int main(int argc, char* argv[]) {

  struct timespec stime, etime;
  double t;

  char* inputFile = argv[1];
  int width, height;

  FILE  *fp    = fopen(inputFile, "r");
  readPPMHeader(fp, &width, &height);
  int size = width*height;

  uchar *imageR, *imageG, *imageB;
  uint *histR, *histG, *histB;

  int imageSize = sizeof(uchar)*size;

  imageR = (uchar*)malloc(imageSize);
  imageG = (uchar*)malloc(imageSize);
  imageB = (uchar*)malloc(imageSize);

  histR = (uint*)calloc(sizeof(uint), 256);
  histG = (uint*)calloc(sizeof(uint), 256);
  histB = (uint*)calloc(sizeof(uint), 256);

  for(uint i = 0; i < size; i++){
    fscanf(fp, "%hhu %hhu %hhu\n", &imageR[i], &imageG[i], &imageB[i]);
  }
  fclose(fp);

  if (clock_gettime(CLOCK_THREAD_CPUTIME_ID , &stime)) {
    fprintf(stderr, "clock_gettime failed");
    exit(-1);
  }
  
  cilk_spawn histogram(imageR, size, histR);
  cilk_spawn histogram(imageG, size, histG);
  histogram(imageB, size, histB);

  if (clock_gettime(CLOCK_THREAD_CPUTIME_ID , &etime)) {
    fprintf(stderr, "clock_gettime failed");
    exit(-1);
  }
  
  t = (etime.tv_sec - stime.tv_sec) + (etime.tv_nsec - stime.tv_nsec) / 1000000000.0;
  
  printf("threads: %d, elapsed time: %lf\n", __cilkrts_get_nworkers(), t);

  /* Print histomgrams */
  /*
  for (uint i = 0; i<256;i++){
    printf("%d) R:%d G:%d B:%d\n", i, histR[i], histG[i], histB[i]);
  }
  */  
  
  return EXIT_SUCCESS;
}
