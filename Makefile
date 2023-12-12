CC = mpicc
CFLAGS = -Wall

all: serial parallel

serial: serial.c
	$(CC) $(CFLAGS) -o quicksort_serial serial.c

parallel: parallel.c
	$(CC) $(CFLAGS) -o parallel parallel.c

clean:
	rm -f quicksort_serial quicksort_parallel
run_serial: serial
	mpirun -np 1 ./quicksort_serial
run_parallel: parallel
	mpirun -np 1 ./quicksort_parallel