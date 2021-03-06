export MPI_HOME=/opt/mpich
export PATH=/opt/intel/bin:$PATH
export PATH=$MPI_HOME/bin:$PATH
export JAVA_HOME=/opt/jdk
export PATH=$JAVA_HOME/bin:$PATH
export SPARK_HOME=/opt/spark
export PATH=$SPARK_HOME/bin:$PATH
export HADOOP_HOME=/opt/hadoop
export PATH=$HADOOP_HOME/bin:$PATH
export HADOOP_CONF_DIR=/tmp/hadoop/configs
export HADOOP_LOG_DIR=/tmp/hadoop/logs
export YARN_LOG_DIR=/tmp/hadoop/yarn-logs
export LD_LIBRARY_PATH=$MPI_HOME/lib:/opt/intel/lib/intel64:$LD_LIBRARY_PATH




