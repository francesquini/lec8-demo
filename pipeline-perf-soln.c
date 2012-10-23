#include <stdio.h>
#include "timing.h"


int main()
{
  int result = 0;

  {
    int a = 0, b = 0;

    timestamp_type t1;
    get_timestamp(&t1);

    for (int ntrips = 0; ntrips < 1000; ++ntrips)
      for (int i = 0; i< 1000*1000; ++i)
      {
        a += i;
        a ++;
      }

    timestamp_type t2;
    get_timestamp(&t2);

    printf("a, a: elapsed time %g s\n",
        timestamp_diff_in_seconds(t1, t2));
    result += a+b;
  }

  {
    int a = 0, b = 0;

    timestamp_type t1;
    get_timestamp(&t1);

    for (int ntrips = 0; ntrips < 1000; ++ntrips)
      for (int i = 0; i< 1000*1000; ++i)
      {
        a += i;
        b ++;
      }

    timestamp_type t2;
    get_timestamp(&t2);

    printf("a, b: elapsed time %g s\n",
        timestamp_diff_in_seconds(t1, t2));
    result += a+b;
  }

  {
    int a = 0, b = 0;

    timestamp_type t1;
    get_timestamp(&t1);

    for (int ntrips = 0; ntrips < 1000; ++ntrips)
      for (int i = 0; i< 250*1000; ++i)
      {
        a += i;
        a ++;
        a += i;
        a ++;
        a += i;
        a ++;
        a += i;
        a ++;
      }

    timestamp_type t2;
    get_timestamp(&t2);

    printf("a, a unrolled: elapsed time %g s\n",
        timestamp_diff_in_seconds(t1, t2));
    result += a+b;
  }
  {
    int a = 0, b = 0;

    timestamp_type t1;
    get_timestamp(&t1);

    for (int ntrips = 0; ntrips < 1000; ++ntrips)
      for (int i = 0; i< 250*1000; ++i)
      {
        a += i;
        b ++;
        a += i;
        b ++;
        a += i;
        b ++;
        a += i;
        b ++;
      }

    timestamp_type t2;
    get_timestamp(&t2);

    printf("a, b unrolled: elapsed time %g s\n",
        timestamp_diff_in_seconds(t1, t2));
    result += a+b;
  }

  return result;
}
