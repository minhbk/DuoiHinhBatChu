#ifndef account_h
#define account_h

#define account_file "account.txt"


typedef struct user{
  char name[20];
  char pass[20];
  int state;
  int id;
  struct user *next;
} User;

void full();
int is_empty_user_list(User *top);
User* make_user(char* name, char* pass);
void add_to_head_user_list(User **top, User *new_user);
int size_of_user_list(User *top);
User* search_user(User *top, char* name);
User* load_data(char* file_name);
void show_list(User* top);
void free_user_list(User** top);
void check_error(int bytes, int client_sock);
void save_user_list(User* user_list, char* file_name);
#endif
