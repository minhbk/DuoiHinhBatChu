#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "account.h"
#include "protocol.h"

void full(){
  printf("NO MEMORY!\n");
}

int is_empty_user_list(User *top){
  return (top == NULL);
}

User* make_user(char* name, char* pass){
  User* user = (User*)malloc(sizeof(User));
  if (user == NULL){
    full();
    exit(1);
  }

  strcpy(user->name, name);
  strcpy(user->pass, pass);
  user->state = AUTHENTICATE;
  user->next = NULL;
  return user;
}

void add_to_head_user_list(User **top, User *new_user){
  new_user->next = (*top);
  (*top) = new_user;
}

int size_of_user_list(User* top){
  User* p;
  int size = 0;
  for (p = top; p != NULL; p = p->next){
    size++;
  }
  return size;
}

User* search_user(User* top, char* name){
  if (is_empty_user_list(top))
          return NULL;

     User* user;
     int kt;

     for (user = top; user != NULL; user = user->next)
     if (strcmp(user->name, name)==0)
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
    add_to_head_user_list(&list, make_user(name, pass ));
  }
  fclose(f);
  return list;
}

void save_user_list(User* user_list){
  FILE *f = fopen(file_name, "w");
  char name[20];
  char pass[20];
  User* list = NULL;
  User* p;

  while (fscanf(f, "%s", name)>0){
    fscanf(f, "%s", pass);
    add_to_head_user_list(&list, make_user(name, pass ));
  }
  fclose(f);

}

void show_list(User* top){
  User* p;
  for(p=top; p!=NULL; p=p->next){
    printf("%s - %s - %d\n", p->name, p->pass);
  }
}


void free_user_list(User** top){
  User *user;
  while (!is_empty_user_list(*top)){
      user=(*top);
      (*top)=user->next;
      free(user);
  }
  (*top)=NULL;
}


void check_error(int bytes, int client_sock){
  if(bytes < 0){
        printf("\nOpss! Network has some error!\n");
        close(client_sock);
        exit(-1);
  }
}
