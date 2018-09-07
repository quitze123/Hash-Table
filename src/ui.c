#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "ui.h"

#define SIZE 2

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

      printf("1. [E] Enter a value into the table.\n");
      printf("2. [P] Print key values.\n");
      printf("3. [R] Remove key.\n");
      printf("4. [Q/q] Quit\n"); 
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
            break;
         case 'r':
            printf("Remove key.\n");
            remove_data(table_info);
            break;
            
      }
   }
}

void remove_data(void ** table_info)
{
   void * user_input = get_user_info();
   remove_node(table_info, user_input);
   free(user_input);

}

void * get_user_info()
{
   int len = 37;
   int c = -1;
   int user_input_len = 0;
   
   void * user_input = calloc(len, sizeof(char));
   if(user_input == NULL)
   {
      perror("calloc(...) failed");
      exit(EXIT_FAILURE);
   }

   printf("Please enter the full name( < 36 chars): ");

   while(c != '\n')
   {
      c = fgetc(stdin);
      if(user_input_len < len)
      {
         ((char *)user_input)[user_input_len] = c;
         user_input_len++;
      }
   }

   ((char *)user_input)[user_input_len - 1] = '\0';

   return user_input;
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
   Node * node = calloc(1,sizeof(Node));
   if(node == NULL)
   {
      perror("calloc(...) failed");
      exit(EXIT_FAILURE);
   }

   node->full_name = get_user_info();

   node->next = NULL;
   node->prev = NULL;
   
   return node;
}
