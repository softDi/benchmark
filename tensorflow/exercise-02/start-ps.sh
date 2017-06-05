bazel-bin/inception/imagenet_distributed_train \
--job_name='ps' \
--task_id=0 \
--ps_hosts='hpc0:2222' \
--worker_hosts='hpc1:2222,hpc2:2222,hpc3:2222'
