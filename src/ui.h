#ifndef UI
#define UI

#include "hash_table.h"

void interface(void ** table_info);
Node * enter_info(void);
void print_table(void * table_info);
void remove_data(void ** table_info);
void * get_user_info();

#endif
