#!/bin/bash
if [ "$1" = "" ] || [ "$2" = "" ] ; then
   echo "Usage : ./setup-network.sh interface node-ID"
else
    sudo ip addr add 192.168.1.$2/24 dev $1 
    sudo ip route add 192.168.1.0/24 dev $1
    sudo ip link set $1 up
    ip addr
fi
