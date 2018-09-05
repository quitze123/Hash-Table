#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "test_functions.h"

void test_insert(void ** table_info)
{
   int size = 25;
   int i = 0;
   
   uint32_t hash_val = 0;
   Node * temp = NULL;

   char names[25][30] = {"Jose Flores", "Cristal Sancez", "Carmen Martinez",
                         "Cesar Castro", "Celia Castro", "Isaiah Espinoza",
                         "Lebron James", "Kevin Durant", "Daniel Cormier",
                         "Robin Whittaker", "Anthony Davis", "Steph Curry",
                         "TJ Dillashaw", "Henry Cejudo", "Ben Simmons",
                         "Kobe Bryant","Draymond Green", "Jose Crus Arriaga",
                         "Emily Garcia", "Josh Diaz", "Moochael Nguey",
                         "Preston Sirois", "JOse Flores", "Stanley Chu",
                         "Viks Vaporru"};
   for(i = 0; i < size; i++)
   {
      hash_val = hash((void *)names[i], strlen(names[i]));
      temp = test_insert_name(names[i]);
      insert(hash_val, temp, table_info);
   }

   print_table(*table_info);
   
   
}

Node * test_insert_name(char * name)
{
   int len = 37;

   Node * node = calloc(1,sizeof(Node));
   if(node == NULL)
   {
      perror("calloc(...) failed");
      exit(EXIT_FAILURE);
   }

   node->full_name = calloc(len, sizeof(char));
   if(node->full_name == NULL)
   {
      perror("calloc(...) failed");
      exit(EXIT_FAILURE);
   }

   node->next = NULL;
   node->prev = NULL;
   
   memcpy(node->full_name, name, strlen(name));

   return node;

}
