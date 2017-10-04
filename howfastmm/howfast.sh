#!/bin/bash
if [[ "$1" == "" ]] || [[ "$2" == "" ]] || [[ "$3" == "" ]] ; then 
	echo "Usage: ./howfast.sh workload method N"
	exit -1
else 
	workload=$1
    method=$2
	N=$3 
    perf stat ./${workload}/${method}/run ${N}
fi 
