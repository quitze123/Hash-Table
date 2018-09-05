#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <error.h>

#include "hash_table.h"

#define TRUE 1
#define FALSE 0

void * run()
{
   void * table_info = NULL;

   table_info = init_table(table_info);

   return table_info;

}

void * init_table(void * table_info)
{
   void ** ht = NULL;
   
   int current_size = 13;

   ht = calloc(current_size, sizeof(Node *));
   if(ht == NULL)
   {
      perror("calloc(...) failed");
      exit(EXIT_FAILURE);
   }

   table_info = calloc(1, sizeof(Table_Info));
   if(table_info == NULL)
   {
      perror("calloc(...) failed");
      exit(EXIT_FAILURE);
   }

   ((Table_Info *)table_info)->size = current_size;
   ((Table_Info *)table_info)->hash_table = ht;
   ((Table_Info *)table_info)->load_factor = 0;

   return table_info;

}

uint32_t hash(void * key, size_t len)
{
   uint32_t hash, i;
    
   for(hash = i = 0; i < len; ++i)
   {
      hash += ((char *)key)[i];
      hash += (hash << 10);
      hash ^= (hash >> 6);
   }
   
   hash += (hash << 3);
   hash ^= (hash >> 11);
   hash += (hash << 15);
   
   return hash;
}

void insert(uint32_t hash_val, Node * node, void ** table_info)
{
   Table_Info ** temp = (Table_Info **)table_info;
   
   Node * temp_node = NULL;

   int key = hash_val % (*temp)->size;
   int empty = is_empty(*temp, key);
   int match = FALSE;

   if(empty == TRUE)
   {
      printf("key : %i\n", key);
      (*temp)->hash_table[key] = node;
      (*temp)->load_factor++;
   }
   else
   {
      temp_node = (*temp)->hash_table[key];
      
      match = is_match(node,temp_node);
      if(match == TRUE)
      {
         free(node->full_name);
         free(node);
      }
      else
      {
         collision(node, &temp_node);
      }
   }
}

void collision(Node * user_node, Node ** node)
{
   Node * temp = *node;

   while(temp->next != NULL)
   {
      temp = temp->next;
   }

   temp->next = user_node;
   user_node->prev = temp;
}

int is_empty(Table_Info * table_info, int key)
{
   if(table_info->hash_table[key] == NULL)
   {
      return TRUE;
   }
   return FALSE;
}

int is_match(Node * user_node, Node * temp_node)
{
   char * name_1 = ((char *)user_node->full_name);
   char * name_2 = ((char *)temp_node->full_name);

   if(strcmp(name_1, name_2) == 0)
   {
      return TRUE;
   }
   return FALSE;
}

void free_table(void * table_info)
{
   Table_Info * temp = (Table_Info *)table_info;
   
   void ** temp_table = temp->hash_table;

   Node * temp_node = NULL;
   Node * temp_search = NULL;
   
   int size = temp->size;
   int i = 0;

   while(i < size)
   {
      if(temp_table[i] != NULL)
      {
         temp_node = temp_table[i];
         temp_search = temp_node;

         while(temp_search->next != NULL)
         {
            free(temp_search->full_name);
            temp_search = temp_search->next;
         }

         free(temp_search->full_name);
         temp_node = temp_search;

         while(temp_search != NULL)
         {
            temp_node = temp_search->prev;
            free(temp_search);
            temp_search = temp_node;
         }
      }
      i++;
   }
   free(temp_table);
   free(temp);
}
