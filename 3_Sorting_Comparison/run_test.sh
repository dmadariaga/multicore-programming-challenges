#!/bin/bash
outfile=results$(date +"%Y-%m-%d-%H:%M:%S").data

echo "threads,time,n,alphabet,cache-misses" >> ${outfile}

iterations=3
for N in 10000 100000 1000000 10000000 # Reference size
do
    for alphabet in 256 2046 32768 1048576 2147483647 # Reference size
    do
        for alg in pqs pms pcs prs # algorithms
        do
            for (( i=0; i<${iterations}; i++)) # repetitions
            do
                for j in 1 2 3 4 5 6 7 8 9 10 11 12 # iterate over cores
                do
        		    echo -n ${alg},${j}, >> ${outfile}
        		    CILK_NWORKERS=${j} perf stat -o perf.tmp -x, -e cache-misses \
              		    ./${alg} ${N} ${alphabet} >> ${outfile}
        		    cut -d, -f1 perf.tmp | sed '/#/d' | sed '/^$/d' \
                                | paste -s | sed 's/\s\+/,/g' >> ${outfile}
        		    echo -e '$-1s/\\n/,/\nx' | ex ${outfile}
        		    echo "ok"
                done
            done
        done
    done
done


rm perf.tmp
