#!/bin/bash

outfile=results$(date +"%Y-%m-%d-%H:%M:%S").data

echo "exp,stime,etime,cache-misses" >> ${outfile}

iterations=3
for exp in test1 test2 test3 test4 test5 # Reference size
do
    for (( i=0; i<${iterations}; i++)) # repetitions
    do
        echo -n ${exp}, >> ${outfile}
        ./get_time >> ${outfile}
	    perf stat -o perf.tmp -x, -e cache-misses ./${exp}.sh
        ./get_time >> ${outfile}
	    cut -d, -f1 perf.tmp | sed '/#/d' | sed '/^$/d' \
                       | paste -s | sed 's/\s\+/,/g' >> ${outfile}
	    echo "ok"
    done
done


rm perf.tmp
