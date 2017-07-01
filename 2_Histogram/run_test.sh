#!/bin/bash

outfile=results$(date +"%Y-%m-%d-%H:%M:%S").data

echo "threads,time,image_size,cache-misses" >> ${outfile}

iterations=3
for IMAGE_SIZE in 2048 4096 8192 # Reference size
do
    for (( i=0; i<${iterations}; i++)) # repetitions
    do
        for j in 1 2 4 6 8 10 12 # iterate over cores
        do
		    echo -n ${j}, >> ${outfile}
		    CILK_NWORKERS=${j} perf stat -o perf.tmp -x, -e cache-misses \
      		    ./histogram_par images/${IMAGE_SIZE}.ppm >> ${outfile}
		    cut -d, -f1 perf.tmp | sed '/#/d' | sed '/^$/d' \
                        | paste -s | sed 's/\s\+/,/g' >> ${outfile}
		    echo -e '$-1s/\\n/,/\nx' | ex ${outfile}
		    echo "ok"
        done
    done
done


rm perf.tmp
