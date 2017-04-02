cmake_minimum_required( VERSION 2.8 )
project(Exercise)

add_executable( Exercise ping_pong.c )

#find_package( MPI REQUIRED )
#if (MPI_FOUND)
#	include_directories(SYSTEM ${MPI_INCLUDE_PATH})
#else (MPI_FOUND)
#	message( SEND_ERROR "This application cannot compile without MPI")
#endif (MPI_FOUND)
#target_link_libraries( Exercise ${MPI_LIBRARIES} )

set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lm" )

#  Manually Set the 3rd-part MPI Library Essentials (Not Portable)
include_directories( "/opt/mpich/include" )
find_library( MPI_LIB NAMES "mpi" PATHS "/opt/mpich/lib" )
target_link_libraries( Exercise ${MPI_LIB} )



