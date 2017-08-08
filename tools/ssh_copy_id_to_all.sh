#!/bin/bash

C_NONE="\033[0m"
C_CYAN="\033[36m"
C_RED="\033[31m"
C_GREEN="\033[32m"
C_ORANGE="\033[33m"
C_BLUE="\033[34m"
C_PURPLE="\033[35m"
C_CYAN="\033[36m"
C_LIGHT_GRAY="\033[37m"

print_misc() {
    echo -e "${C_PURPLE} $1 ${C_NONE}"
}

print_info() {
    echo -e "${C_BLUE} $1 ${C_NONE}"
}

print_error() {
    echo -e "${C_RED} $1 ${C_NONE}"
}

print_warning() {
    echo -e "${C_ORANGE} $1 ${C_NONE}"
}

print_misc "Bash version ${BASH_VERSION}."

if [[ "$1" == "" ]]
then
	print_error "Usage: ./ssh_copy_id_to_all.sh NumOfHosts(includes master node)"
	exit -1
fi
num_nodes=$1
echo "" > hosts.txt 
for ((i = 2; i <= ${num_nodes}+1; i++)); do
     sshpass -p 'root' ssh-copy-id 172.17.0.$i
done
print_info "Copying is done."

count=0;
for ((i = 2; i <= ${num_nodes}+1; i++)); do 
    ssh 172.17.0.$i hostname
done
print_info "Testing is done."

