#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "ui.h"

#define SIZE 2

void find_key(void * key)
{
   printf("%s\n", (char *)key);
}

void interface(void ** table_info)
{
   int i = 0;
   int c = 0;

   uint32_t hash_val = 0;

   char input[SIZE] = {0, 0};

   Node * node = NULL;

   while(input[0] != 'q' && input[0] != 'Q')
   {
      c = -1;
      i = 0;

      printf("1. [E/e] Enter a value into the table.\n");
      printf("2. [P/p] Print key values.\n");
      printf("3. [Q/q] Quit\n"); 
      printf("\nEnter your choice : ");
      while(c != '\n')
      {
         c = fgetc(stdin);
         if(i < SIZE)
            input[i] = c;
         i++;
      }
      
      c = tolower(input[0]);

      switch(c)
      {
         case 'e':
            node = enter_info();
            hash_val = hash(node->full_name, strlen((char *)node->full_name));
            insert(hash_val, node, table_info);
            break;
         case 'p':
            print_table(*table_info);
      }
   }
}

void print_table(void * table_info)
{
   void ** temp = ((Table_Info *)table_info)->hash_table;

   Node * node = NULL;
   
   int size = ((Table_Info *)table_info)->size;
   int i = 0;

   while(i < size)
   {
      node = (Node *)temp[i];
      if(node != NULL)
      {
         while(node != NULL)
         {
            printf("Index : %i %s\n", i,(char *)(node->full_name));
            node = node->next;
         }
      }
      i++;
   }
}

Node * enter_info(void)
{
   int len = 37;
   int c = -1;
   int user_name_len = 0;

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
   
   printf("Please enter the full name( < 36 chars): ");
   
   while(c != '\n')
   {
      c = fgetc(stdin);
      if(user_name_len < len)
      {
         ((char *)node->full_name)[user_name_len] = c;
         user_name_len++;
      }
   }

   ((char *)node->full_name)[user_name_len - 1] = '\0';

   return node;
}
