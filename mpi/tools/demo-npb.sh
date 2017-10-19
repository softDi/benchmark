#!/bin/bash 
~/benchmark/tools/ssh_copy_id_to_all.sh 4
~/benchmark/tools/genhosts.sh 4
mpirun -n 4 -f hosts.txt benchmark/mpi/NPB3.3-MPI/bin/bt.A.4
