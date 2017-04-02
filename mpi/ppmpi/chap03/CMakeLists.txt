set( MPI_LIB_PATH "/opt/mpich/lib" )
set( MPI_INC_PATH "/opt/mpich/include" )

add_executable( greetings greetings.c )

include_directories( ${MPI_INC_PATH} )
find_library( MPI_LIB NAMES "mpi" PATHS ${MPI_LIB_PATH} )
target_link_libraries( greetings ${MPI_LIB} )


