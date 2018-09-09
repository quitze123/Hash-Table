#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "test_functions.h"

void test_insert(void ** table_info)
{
   int size = 32;
   int i = 0;
   
   uint32_t hash_val = 0;
   Node * temp = NULL;

   char names[32][37] = {"Jose Flores", "Cristal Sancez", "Carmen Martinez",
                         "Cesar Castro", "Celia Castro", "Isaiah Espinoza",
                         "Lebron James", "Kevin Durant", "Daniel Cormier",
                         "Robin Whittaker", "Anthony Davis", "Steph Curry",
                         "TJ Dillashaw", "Henry Cejudo", "Ben Simmons",
                         "Kobe Bryant","Draymond Green", "Jose Crus Arriaga",
                         "Emily Garcia", "Josh Diaz", "Moochael Nguey",
                         "Preston Sirois", "JOse Flores", "Stanley Chu",
                         "Viks Vaporru", "Vince", "Jordan", "Tara Smith", 
                         "Beth Vordova", "Advising", "lfdjkslkjf sdjkfl kdfjls",
                         "ajajajajuqmkeoxlaqoncdludl8882h1h3h3"};

   for(i = 0; i < size; i++)
   {
      hash_val = hash((void *)names[i], strlen(names[i]));
      temp = test_insert_name(names[i]);
      insert(hash_val, temp, table_info);
   }

   
   
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


void test_remove(void ** table_info)
{
   int size = 9;
   int i = 0;

   char remove_names[9][37] = {"Robin Whittaker", "Jose Crus Arriaga", "Cesar Castro", 
                               "Henry Cejudo", "ajajajajuqmkeoxlaqoncdludl8882h1h3h3",
                               "Jose Flores", "This name is not here.",
                               "Lebron James", "Jose Flores"};
   for(i = 0; i < size; i++)
   {
      printf("Removing : %s\n", remove_names[i]);
      remove_node(table_info, (void *)remove_names[i]);
      printf("Removed : %s\n", remove_names[i]);
   }

   print_table(*table_info);
}
