#include <stdio.h>
#include <float.h>
#include "timing.h"


int main()
{
  int result = 0;

  {
    double very_small = DBL_MIN * 1e-9;
    printf("very_small: %g\n", very_small);
    printf("DBL_MIN: %g\n", DBL_MIN);

    double factor = 5;

    timestamp_type t1;
    get_timestamp(&t1);

    for (int ntrips = 0; ntrips < 100; ++ntrips)
    {
      double a = 0;
      for (int i = 0; i< 1000*1000; ++i)
      {
        a = a + i*factor;
      }
      result += a;
    }

    timestamp_type t2;
    get_timestamp(&t2);

    printf("elapsed time %g s\n",
        timestamp_diff_in_seconds(t1, t2));
  }
  return result;
}

