if [ "$1" == "" ] ; then 
	echo "Usage: ./start-ps.sh NodeID"
	exit -1
else 
	nid=$1
	python tf_cnn_benchmarks.py --local_parameter_device=cpu --num_gpus=1 \
--batch_size=32 --model=resnet50 --variable_update=distributed_replicated \
--job_name=ps --ps_hosts=192.168.0.100:50000,192.168.0.101:50000 \
--worker_hosts=192.168.0.100:50001,192.168.0.101:50001 --task_index=${nid} \
--data_dir=/mnt/dataset/imagenet
fi 
