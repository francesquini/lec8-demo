EXECUTABLES = \
	      mpi-bandwidth mpi-bi-bandwidth mpi-latency \
	      perf-mystery

all: $(EXECUTABLES)

perf-mystery: perf-mystery.cpp
	g++ $(DEBUG_FLAGS) -lrt -o$@ $^

mpi%: mpi%.c
	mpicc -std=gnu99 $(DEBUG_FLAGS) -lrt -o$@ $^

clean:
	rm -f $(EXECUTABLES) *.o mpe-*
