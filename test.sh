#!/bin/bash

cd programs
make
cd ..

for file in results/*.res
do
	rm -f $file
done

echo ""
echo ""
echo "================================ TESTS ==============================="

cd programs

#echo "===> Running CPU, small (10), SCHED_OTHER..."
#sudo /usr/bin/time --verbose --output=../results/cpu_s_other.res ./cpuprog 10 SCHED_OTHER
#echo "===> Running CPU, small (10), SCHED_FIFO..."
#sudo /usr/bin/time --verbose --output=../results/cpu_s_fifo.res ./cpuprog 10 SCHED_FIFO
#echo "===> Running CPU, small (10), SCHED_RR..."
#sudo /usr/bin/time --verbose --output=../results/cpu_s_rr.res ./cpuprog 10 SCHED_RR

#echo "===> Running CPU, medium (100), SCHED_OTHER..."
#sudo /usr/bin/time --verbose --output=../results/cpu_m_other.res ./cpuprog 100 SCHED_OTHER
#echo "===> Running CPU, medium (100), SCHED_FIFO..."
#sudo /usr/bin/time --verbose --output=../results/cpu_m_fifo.res ./cpuprog 100 SCHED_FIFO
#echo "===> Running CPU, medium (100), SCHED_RR..."
#sudo /usr/bin/time --verbose --output=../results/cpu_m_rr.res ./cpuprog 100 SCHED_RR

#echo "===> Running CPU, large (1000), SCHED_OTHER..."
#sudo /usr/bin/time --verbose --output=../results/cpu_l_other.res ./cpuprog 1000 SCHED_OTHER
#echo "===> Running CPU, large (1000), SCHED_FIFO..."
#sudo /usr/bin/time --verbose --output=../results/cpu_l_fifo.res ./cpuprog 1000 SCHED_FIFO
#echo "===> Running CPU, large (1000), SCHED_RR..."
#sudo /usr/bin/time --verbose --output=../results/cpu_l_rr.res ./cpuprog 1000 SCHED_RR

#echo "===> Running IO, small (10), SCHED_OTHER..."
#sudo /usr/bin/time --verbose --output=../results/io_s_other.res ./ioprog 10 SCHED_OTHER
#echo "===> Running IO, small (10), SCHED_FIFO..."
#sudo /usr/bin/time --verbose --output=../results/io_s_fifo.res ./ioprog 10 SCHED_FIFO
#echo "===> Running IO, small (10), SCHED_RR..."
#sudo /usr/bin/time --verbose --output=../results/io_s_rr.res ./ioprog 10 SCHED_RR

#echo "===> Running IO, medium (100), SCHED_OTHER..."
#sudo /usr/bin/time --verbose --output=../results/io_m_other.res ./ioprog 100 SCHED_OTHER
#echo "===> Running IO, medium (100), SCHED_FIFO..."
#sudo /usr/bin/time --verbose --output=../results/io_m_fifo.res ./ioprog 100 SCHED_FIFO
#echo "===> Running IO, medium (100), SCHED_RR..."
#sudo /usr/bin/time --verbose --output=../results/io_m_rr.res ./ioprog 100 SCHED_RR

#echo "===> Running IO, large (1000), SCHED_OTHER..."
#sudo /usr/bin/time --verbose --output=../results/io_l_other.res ./ioprog 1000 SCHED_OTHER
#echo "===> Running IO, large (1000), SCHED_FIFO..."
#sudo /usr/bin/time --verbose --output=../results/io_l_fifo.res ./ioprog 1000 SCHED_FIFO
#echo "===> Running IO, large (1000), SCHED_RR..."
#sudo /usr/bin/time --verbose --output=../results/io_l_rr.res ./ioprog 1000 SCHED_RR

cd ..

echo "======================================================================"
echo ""
echo ""

cd programs
make clean
cd ..

echo "Done"
