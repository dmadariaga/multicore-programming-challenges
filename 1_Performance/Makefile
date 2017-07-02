all: random_char pqs pps psm

random_char: 
	gcc -std=gnu99 -o genchars generate_random_chars.c

pqs: 
	g++ -std=c++11 -o pqs parallel_quick_sort.cpp -fcilkplus -lcilkrts -lrt

pps:
	gcc -std=gnu99 -o ps prefix_sum.c -fcilkplus -lcilkrts -lm -lrt

psm:
	gcc -std=gnu99 -o sm string_matching.c -fcilkplus -lcilkrts

clean:
	rm -f *.o
	rm -f random_char pqs pps psm
