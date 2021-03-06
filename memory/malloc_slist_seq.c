/**
 * Singly-linked list sequential allocation with malloc.
 */

#include <sys/queue.h>
#include <stdlib.h>

#include "test.h"
#include "slist.h"

BEGIN_TEST_SUIT("malloc_slist_seq")

long start_time;
Slist slist;
Slist_item *item;
SLIST_INIT(&slist);

BEGIN_TEST_CASE("primary_allocation", long, "%ld")
{
  for (int i = 0; i < TEST_MULTIPLIER; i++)
  {
    start_time = get_cpu_time();
    item = xmalloc(sizeof(Slist_item));
    SLIST_INSERT_HEAD(&slist, item, entries);
    metric += get_cpu_time() - start_time;
  }
}
END_TEST_CASE

BEGIN_TEST_CASE("primary_deallocation", long, "%ld")
{
  while (!SLIST_EMPTY(&slist))
  {
    start_time = get_cpu_time();
    item = SLIST_FIRST(&slist);
    SLIST_REMOVE_HEAD(&slist, entries);
    free(item);
    metric += get_cpu_time() - start_time;
  }
}
END_TEST_CASE

BEGIN_TEST_CASE("secondary_allocation", long, "%ld")
{
  for (int i = 0; i < TEST_MULTIPLIER; i++)
  {
    start_time = get_cpu_time();
    item = xmalloc(sizeof(Slist_item));
    SLIST_INSERT_HEAD(&slist, item, entries);
    metric += get_cpu_time() - start_time;
  }
}
END_TEST_CASE

BEGIN_TEST_CASE("secondary_deallocation", long, "%ld")
{
  while (!SLIST_EMPTY(&slist))
  {
    start_time = get_cpu_time();
    item = SLIST_FIRST(&slist);
    SLIST_REMOVE_HEAD(&slist, entries);
    free(item);
    metric += get_cpu_time() - start_time;
  }
}
END_TEST_CASE

END_TEST_SUIT
