EXECUTABLES = \
	      mpi-bandwidth mpi-bi-bandwidth mpi-latency \
	      perf-mystery numa-test

all: $(EXECUTABLES)

perf-mystery: perf-mystery.cpp
	g++ $(DEBUG_FLAGS) -lrt -o$@ $^

numa-test: numa-test.c
	gcc -std=gnu99 -fopenmp $(DEBUG_FLAGS) -lrt -lnuma -o$@ $^

mpi%: mpi%.c
	mpicc -std=gnu99 $(DEBUG_FLAGS) -lrt -o$@ $^

clean:
	rm -f $(EXECUTABLES) *.o mpe-*
