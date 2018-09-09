#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "hash_table.h"
#include "ui.h"
#include "test_functions.h"

enum Tests
{
   INSERT, LOOKUP, REMOVE
};

void usage()
{
   printf("usage : ./a.out [INSERT=0, LOOKUP=1, REMOVE=2]\n");
}

int convert_num(char * arg)
{
   int num = atoi(arg);

   return num;
}

int main(int argc, char ** argv)
{
   void * table_info = run();

   int RUN_TEST = -1;

   if(argc > 1 && argc <= 2)
   {
      RUN_TEST = convert_num(argv[1]);

      if(RUN_TEST == INSERT)
      {
         test_insert(&table_info);
      }
      else if(RUN_TEST == LOOKUP)
      {
         printf("Test lookup.\n");
      }
      else
      {
         test_insert(&table_info);
         test_remove(&table_info);
      }
   }
   else if(argc > 2)
   {
      usage();
   }
   else
   {
      interface(&table_info);
   }

   free_table(table_info);

   return 0;
}
