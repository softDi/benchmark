#!/bin/sh
if [ "$(hostname)" == "hpc0" ] ; then 
    echo "As ps0." && exit 0
python trainer.py \
    --ps_hosts=hpc0:2222 \
    --worker_hosts=hpc1:2222,hpc2:2222,hpc3:2222 \
    --job_name=ps --task_index=0
else 
    echo "This is Node-$(sed \'s/hpc//g\') "
    echo "Act as a worker." && exit 0
    python trainer.py \
    --ps_hosts=hpc0:2222 \
    --worker_hosts=hpc1:2222,hpc2:2222,hpc3:2222 \
    --job_name=worker --task_index=$(sed 's/hpc//g')
    
fi 

