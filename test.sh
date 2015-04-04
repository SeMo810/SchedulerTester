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

echo "===> Running CPU, small (10), SCHED_OTHER..."
sudo /usr/bin/time --verbose --output=results/cpu_s_other.res programs/cpuprog 10 SCHED_OTHER
echo "===> Running CPU, small (10), SCHED_FIFO..."
sudo /usr/bin/time --verbose --output=results/cpu_s_fifo.res programs/cpuprog 10 SCHED_FIFO
echo "===> Running CPU, small (10), SCHED_RR..."
sudo /usr/bin/time --verbose --output=results/cpu_s_rr.res programs/cpuprog 10 SCHED_RR

echo "===> Running CPU, medium (100), SCHED_OTHER..."
sudo /usr/bin/time --verbose --output=results/cpu_m_other.res programs/cpuprog 100 SCHED_OTHER
echo "===> Running CPU, medium (100), SCHED_FIFO..."
sudo /usr/bin/time --verbose --output=results/cpu_m_fifo.res programs/cpuprog 100 SCHED_FIFO
echo "===> Running CPU, medium (100), SCHED_RR..."
sudo /usr/bin/time --verbose --output=results/cpu_m_rr.res programs/cpuprog 100 SCHED_RR

echo "===> Running CPU, large (1000), SCHED_OTHER..."
sudo /usr/bin/time --verbose --output=results/cpu_l_other.res programs/cpuprog 1000 SCHED_OTHER
echo "===> Running CPU, large (1000), SCHED_FIFO..."
sudo /usr/bin/time --verbose --output=results/cpu_l_fifo.res programs/cpuprog 1000 SCHED_FIFO
echo "===> Running CPU, large (1000), SCHED_RR..."
sudo /usr/bin/time --verbose --output=results/cpu_l_rr.res programs/cpuprog 1000 SCHED_RR


echo "======================================================================"
echo ""
echo ""

cd programs
make clean
cd ..

echo "Done"
