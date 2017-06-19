bazel-bin/inception/imagenet_distributed_train \
--batch_size=128 \
--data_dir=/mnt/qnap/ImageNet_Dataset/imagenet-data \
--job_name='worker' \
--task_id=0 \
--ps_hosts='hpc0:2222' \
--worker_hosts='hpc1:2222,hpc2:2222,hpc3:2222'
