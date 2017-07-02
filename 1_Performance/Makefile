all: genchars pqs ps sm get_time

genchars: 
	gcc -std=gnu99 -o genchars generate_random_chars.c

get_time: 
	g++ -std=c++11 -o get_time get_time.cpp -lrt

pqs: 
	g++ -std=c++11 -o pqs parallel_quick_sort.cpp -fcilkplus -lcilkrts -lrt

ps:
	gcc -std=gnu99 -o ps prefix_sum.c -fcilkplus -lcilkrts -lm -lrt

sm:
	gcc -std=gnu99 -o sm string_matching.c -fcilkplus -lcilkrts -lrt

clean:
	rm -f *.o
	rm -f genchars pqs ps sm get_time
