#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "hash_table.h"
#include "ui.h"
#include "test_functions.h"

#define TEST 1
#define RUN_TEST 0

enum Tests
{
   INSERT, LOOKUP, REMOVE
};

int main(void)
{
   void * table_info = run();

   if(TEST)
   {
      if(RUN_TEST == INSERT)
         test_insert(&table_info);
   }
   else
   {
      interface(&table_info);
   }

   free_table(table_info);
   return 0;
}
