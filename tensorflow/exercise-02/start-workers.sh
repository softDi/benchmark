bazel-bin/inception/imagenet_distributed_train \
--batch_size=32 \
--data_dir=/mnt/qnap/ImageNet_Dataset/imagenet-data \
--job_name='worker' \
--task_id=0 \
--ps_hosts='localhost:2222' \
--worker_hosts='localhost:2222'
