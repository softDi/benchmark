```
Download mpich-3.2 from https://www.mpich.org/downloads/
tar -xvf ~/Downloads/mpich-3.2.tar.gz
./configure --prefix=/opt/mpich --disable-fortran CC=gcc CXX=g++
make 
sudo make install
export PATH=/opt/mpich/bin:$PATH
cd benchmark/mpi/exercise-01
make 
mpirun -n 4 ./exercise 
```
