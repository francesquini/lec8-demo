EXECUTABLES = \
	      pipeline-perf-mystery \
	      pipeline-perf pipeline-perf-soln pipeline-perf-soln-o3 \
	      fp-perf

all: $(EXECUTABLES)

pipeline-perf-mystery: pipeline-perf-mystery.cpp
	g++ $(DEBUG_FLAGS) -lrt -o$@ $^

pipeline-perf: pipeline-perf.c
	gcc -O -std=gnu99 -fopenmp $(DEBUG_FLAGS) -lrt -o$@ $^

pipeline-perf-soln: pipeline-perf-soln.c
	gcc -O -std=gnu99 -fopenmp $(DEBUG_FLAGS) -lrt -o$@ $^

pipeline-perf-soln-o3: pipeline-perf-soln.c
	gcc -O3 -std=gnu99 -fopenmp $(DEBUG_FLAGS) -lrt -o$@ $^

fp-perf: fp-perf.c
	gcc -O3 -std=gnu99 $(DEBUG_FLAGS) -lrt -o$@ $^

clean:
	rm -f $(EXECUTABLES) *.o mpe-*
