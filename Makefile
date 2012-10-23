EXECUTABLES = \
	      mpi-bandwidth mpi-bi-bandwidth mpi-latency \
	      pipeline-perf-mystery \
	      pipeline-perf pipeline-perf-soln pipeline-perf-soln-o3 \
	      numa-test count3s

all: $(EXECUTABLES)

pipeline-perf-mystery: pipeline-perf-mystery.cpp
	g++ $(DEBUG_FLAGS) -lrt -o$@ $^

pipeline-perf: pipeline-perf.c
	gcc -O -std=gnu99 -fopenmp $(DEBUG_FLAGS) -lrt -o$@ $^

pipeline-perf-soln: pipeline-perf-soln.c
	gcc -O -std=gnu99 -fopenmp $(DEBUG_FLAGS) -lrt -o$@ $^

pipeline-perf-soln-o3: pipeline-perf-soln.c
	gcc -O3 -std=gnu99 -fopenmp $(DEBUG_FLAGS) -lrt -o$@ $^

numa-test: numa-test.c
	gcc -O3 -std=gnu99 -fopenmp $(DEBUG_FLAGS) -lrt -lnuma -o$@ $^

count3s: count3s.c
	gcc -O0 -std=gnu99 -fopenmp $(DEBUG_FLAGS) -lrt -o$@ $^

mpi%: mpi%.c
	mpicc -std=gnu99 $(DEBUG_FLAGS) -lrt -o$@ $^

clean:
	rm -f $(EXECUTABLES) *.o mpe-*
