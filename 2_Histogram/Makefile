CFLAGS= -g -fcilkplus -lcilkrts -std=c99 -lrt

all: histogram_par random_rgb_image

histogram_par: 
	gcc -std=gnu99 -o histogram_par histogram_par.c -fcilkplus -lcilkrts -lrt

random_rgb_image: 
	gcc -o random_rgb random_rgb_image.c

clean:
	rm -f *.o
	rm -f histogram_par random_rgb
