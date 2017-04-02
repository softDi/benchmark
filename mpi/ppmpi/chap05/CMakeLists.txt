cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
#cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
#project(mancos-gather)
#
#add_executable(mancos-gather "gather.cpp") 
##Boost may be used in the future for graph analysis. Gem5-aladin also use boost-graph
#include_directories("/opt/boost")
#include_directories("../include")
#include_directories("../scatter/include")
#include_directories(".")
#
#
##ns3
##set(NS3_DIR "/opt/ns3" )
##include_directories(${NS3_DIR})
##set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} ${NS3_DIR})
##find_library( NS3_AODV_LIB NAMES "ns3.26-aodv-debug" PATHS ${NS3_DIR} )
##find_library( NS3_INTERNET_LIB NAMES "ns3.26-internet-debug" PATHS ${NS3_DIR} )
##find_library( NS3_NETWORK_LIB NAMES "ns3.26-network-debug" PATHS ${NS3_DIR} )
##find_library( NS3_STATS_LIB NAMES "ns3.26-stats-debug" PATHS ${NS3_DIR} )
##find_library( NS3_CORE_LIB NAMES "ns3.26-core-debug" PATHS ${NS3_DIR} )
##find_library( NS3_APPS_LIB NAMES "ns3.26-applications-debug" PATHS ${NS3_DIR} )
##find_library( NS3_P2P_LIB NAMES "ns3.26-point-to-point-debug" PATHS ${NS3_DIR} )
##find_library( NS3_CSMA_LIB NAMES "ns3.26-csma-debug" PATHS ${NS3_DIR} )
##find_library( NS3_CSMA_LAYOUT_LIB NAMES "ns3.26-csma-layout-debug" PATHS ${NS3_DIR} )
##find_library( NS3_NETANIM_LIB NAMES "ns3.26-netanim-debug" PATHS ${NS3_DIR} )
##find_library( NS3_P2P_LAYOUT_LIB NAMES "ns3.26-point-to-point-layout-debug" PATHS ${NS3_DIR} )
##set( NS3_LIBS ${NS3_AODV_LIB} ${NS3_INTERNET_LIB} ${NS3_NETWORK_LIB} ${NS3_STATS_LIB} ${NS3_CORE_LIB} ${NS3_APPS_LIB} ${NS3_P2P_LIB} ${NS3_CSMA_LIB} ${NS3_CSMA_LAYOUT_LIB} ${NS3_NETANIM_LIB} ${NS3_P2P_LAYOUT_LIB} ${NS3_P2P_LAYOUT_LIB} )
##
## mancos/core contains basis data structures
#set(MANCOS_SCATTER_DIR "~/workspace/mancos/cosim/scatter/build" )
#include_directories(${MANCOS_SCATTER_DIR})
#find_library( MANCOS_LIBS NAMES "mancos-scatter" PATHS ${MANCOS_SCATTER_DIR} )
#
#MESSAGE( STATUS "MANCOS_LIBS = " ${MANCOS_LIBS} )
#MESSAGE( STATUS "NS3_LIBS = " ${NS3_LIBS} )
#
#target_link_libraries (mancos-gather ${MANCOS_LIBS} )
#target_link_libraries (mancos-gather ${NS3_LIBS})
