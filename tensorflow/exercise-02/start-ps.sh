bazel-bin/inception/imagenet_distributed_train \
--job_name='ps' \
--task_id=0 \
--ps_hosts='localhost:2222' \
--worker_hosts='localhost:2222'
