#ifndef HASH_TABLE
#define HASH_TABLE

#include <stdint.h>
#include <stdio.h>

typedef struct table_info
{
   void ** hash_table;
   int size;
   int load_factor;
}Table_Info;

typedef struct node
{
   void * full_name;
   int number;
   struct node * next;
   struct node * prev;
}Node;

void * run();
void * init_table();
uint32_t hash(void * key, size_t len);
void insert(uint32_t hash_val, Node * node, void ** table_info);
int is_empty(Table_Info * table_info, int key);
int is_match(Node * user_node, Node * temp_node);
void free_table(void * table_info);
void collision(Node * user_info, Node ** node);
#endif
