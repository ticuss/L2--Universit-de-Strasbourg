#!/bin/sh

PARAMS="-Wall -Wextra -O2"
TEST_FILE="/bin/vim"
TMP=""
RTIME=0
UTIME=0
STIME=0

echo "Compiling getchar() version..."
gcc -o lib.out $PARAMS 5-7-lib.c > /dev/null
echo "Compiling mygetchar() version..."
gcc -o my.out $PARAMS 5-7.c > /dev/null

echo "\nTesting getchar()..."
for i in {1..10}; do
	(time ./lib.out < $TEST_FILE > /dev/null) 2> bench
	sed -e "s/,/./g" bench > bench_p && mv bench_p bench
	TMP=$(cat bench | grep -Po "real\s0m\K.*?(?=s)")
	RTIME=$( bc -l <<< "$RTIME + $TMP" )
	echo $TMP $RTIME
	TMP=$(cat bench | grep -Po "user\s0m\K.*?(?=s)")
	UTIME=$( bc -l <<< "$UTIME + $TMP" )
	TMP=$(cat bench | grep -Po "sys\s0m\K.*?(?=s)")
	STIME=$( bc -l <<< "$STIME + $TMP" )
done
echo -e "\nrealtime (avg) = $(bc -l <<< "$RTIME / 10.0")"
echo "usertime (avg) = $(bc -l <<< "$UTIME / 10.0")"
echo "systime  (avg) = $(bc -l <<< "$STIME / 10.0")"

for N in {8,16,32,64,128,256,512,1024,2048,4096}; do
	RTIME=0
	UTIME=0
	STIME=0
	echo -e "\nTesting mygetchar($N)..."
	for i in {1..10}; do
		(time ./my.out $N < $TEST_FILE > /dev/null) 2> bench
		sed -e "s/,/./g" bench > bench_p && mv bench_p bench
		TMP=$(cat bench | grep -Po "real\s0m\K.*?(?=s)")
		RTIME=$( bc -l <<< "$RTIME + $TMP" )
		TMP=$(cat bench | grep -Po "user\s0m\K.*?(?=s)")
		UTIME=$( bc -l <<< "$UTIME + $TMP" )
		TMP=$(cat bench | grep -Po "sys\s0m\K.*?(?=s)")
		STIME=$( bc -l <<< "$STIME + $TMP" )
	done
	echo "realtime (avg) = $( bc -l <<< "$RTIME / 10.0")"
	echo "usertime (avg) = $( bc -l <<< "$UTIME / 10.0")"
	echo "systime  (avg) = $( bc -l <<< "$STIME / 10.0")"
done
