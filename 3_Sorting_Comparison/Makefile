all: ss pqs pms pcs prs

ss: 
	g++ -std=c++11 -o ss sequential_sort.cpp -lrt

pqs: 
	g++ -std=c++11 -o pqs parallel_quick_sort.cpp -fcilkplus -lcilkrts -lrt

pms: 
	g++ -std=c++11 -o pms parallel_merge_sort.cpp -fcilkplus -lcilkrts -lrt

pcs: 
	gcc -std=gnu99 -o pcs parallel_counting_sort.c -fcilkplus -lcilkrts -lrt

prs: 
	g++ -std=c++11 -o prs parallel_radix_sort.cpp -fcilkplus -lcilkrts -lrt

clean:
	rm -f *.o
	rm -f ss pqs pms pcs prs
