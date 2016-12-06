#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct a{
  char name[20];
  char pass[20];
  int status;
  int id;
  struct a *next;
} User;

void full();
int is_empty(User *top);
User* make_user(char* name, char* pass, int id);
void add_to_head(User **top, User *new_user);
int size_of_list(User *top);
User* search(User *top, int id);
User* load_data(char* file_name);
void show_list(User* top);
void free_list(User** top);
