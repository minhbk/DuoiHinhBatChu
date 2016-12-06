#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "account.h"

void full(){
  printf("NO MEMORY!\n");
}

int is_empty(User *top){
  return (top == NULL);
}

User* make_user(char* name, char* pass, int id){
  User* user = (User*)malloc(sizeof(User));
  if (user == NULL){
    full();
    exit(1);
  }

  strcpy(user->name, name);
  strcpy(user->pass, pass);
  user->status = 0;
  user->id = id;
  return user;
}

void add_to_head(User **top, User *new_user){
  new_user->next = (*top);
  (*top) = new_user;
}

int size_of_list(User* top){
  User* p;
  int size = 0;
  for (p = top; p != NULL; p = p->next){
    size++;
  }
  return size;
}

User* search(User* top, int id){
  if (is_empty(top))
          return NULL;

     User* user;
     int kt;

     for (user = top; user != NULL; user = user->next)
     if (user->id == id)
     {
          kt=1;
          break;
     }

     if (kt)
          return user;
     else
          return NULL;
}

User* load_data(char* file_name){
  FILE *f = fopen(file_name, "r");
  char name[20];
  char pass[20];
  User* list = NULL;
  User* p;

  while (fscanf(f, "%s", name)>0){
    fscanf(f, "%s", pass);
    add_to_head(&list, make_user(name, pass, size_of_list(list)));
  }
  fclose(f);
  return list;
}

void show_list(User* top){
  User* p;
  for(p=top; p!=NULL; p=p->next){
    printf("%s - %s - %d\n", p->name, p->pass, p->id);
  }
}


void free_list(User** top){
  User *user;
  while (!is_empty(*top)){
      user=(*top);
      (*top)=user->next;
      free(user);
  }
  (*top)=NULL;
}
