#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "hash_table.h"
#include "ui.h"
#include "test_functions.h"


int main(void)
{
   void * table_info = run();
   test_insert(&table_info);
   /*
   interface(&table_info);
   */
   free_table(table_info);
   return 0;
}
