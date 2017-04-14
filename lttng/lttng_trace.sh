#!/bin/sh
#lttng list --kernel
#lttng list --kernel --syscall
lttng create my-kernel-session --output=/tmp/my-kernel-trace
lttng enable-event --kernel sched_switch,sched_process_fork
lttng enable-event --kernel --syscall open,close
#lttng enable-event --kernel --all
lttng start 

### Do Something

lttng stop
lttng destroy
chown -R $(whoami) /tmp/my-kernel-trace


### Analysis
babeltrace ~/lttng-traces/my-user-space-session*
babeltrace /tmp/my-kernel-trace | grep _open | wc --lines
sudo dnf -y install python3-babeltrace
python3 top5proc.py /tmp/my-kernel-trace/kernel
