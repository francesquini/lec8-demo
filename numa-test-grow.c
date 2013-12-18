// Based on numatest.cpp by James Brock
// http://stackoverflow.com/questions/7259363/measuring-numa-non-uniform-memory-access-no-observable-asymmetry-why
//
// Changes by Andreas Kloeckner, 10/2012:
// - Rewritten in C + OpenMP
// - Added contention tests

#define _GNU_SOURCE
#include <numa.h>
#include <sched.h>
#include <stdio.h>
#include <pthread.h>
#include <omp.h>
#include <assert.h>
#include "timing.h"

void pin_to_core(size_t core)
{
  cpu_set_t cpuset;
  CPU_ZERO(&cpuset);
  CPU_SET(core, &cpuset);
  pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);
}

void print_bitmask(const struct bitmask *bm)
{
  for(size_t i=0; i<bm->size; ++i)
    printf("%d", numa_bitmask_isbitset(bm, i));
}


double measure_access(void *x, size_t array_size, size_t ntrips)
{
  timestamp_type t1;
  get_timestamp(&t1);

  for (size_t i = 0; i<ntrips; ++i)
    for(size_t j = 0; j<array_size; ++j)
    {
      *(((char*)x) + ((j * 1009) % array_size)) += 1;
    }

  timestamp_type t2;
  get_timestamp(&t2);

  return timestamp_diff_in_seconds(t1, t2);
}


int main(int argc, const char **argv)
{
  int num_cpus = numa_num_task_cpus();
  printf("num cpus: %d\n", num_cpus);

  printf("numa available: %d\n", numa_available());
  numa_set_localalloc();

  struct bitmask *bm = numa_bitmask_alloc(num_cpus);
  for (int i=0; i<=numa_max_node(); ++i)
  {
    numa_node_to_cpus(i, bm);
    printf("numa node %d ", i);
    print_bitmask(bm);
    printf(" - %g GiB\n", numa_node_size(i, 0) / (1024.*1024*1024.));
  }
  numa_bitmask_free(bm);

  puts("");

  char *x;
  const size_t cache_line_size = 64;
  const size_t array_size = 512*1024*1024;
  size_t ntrips = 2;

#pragma omp parallel
  {
    assert(omp_get_num_threads() == num_cpus);
    int tid = omp_get_thread_num();

    pin_to_core(tid);
    if(tid == 0)
      x = (char *) numa_alloc_local(array_size);

    // {{{ single access
#pragma omp barrier
    for (size_t i = 0; i<num_cpus; ++i)
    {
      if (tid == i)
      {
	for (size_t csize = 64; csize <= array_size; csize *=2) {
          double t = measure_access(x, csize, ntrips);
          printf("%zu\t0\t%g\t%g\t%zu\n",
              i, array_size*ntrips*cache_line_size / t / 1e6, t, csize);
        }
      }
#pragma omp barrier
    }
    // }}}
  }
  numa_free(x, array_size);

  return 0;
}
