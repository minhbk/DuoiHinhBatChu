#include <stdio.h>
#include <stdlib.h>
#include "account.h"

int main(){
  User* list;
  list = load_data("account.txt");
  show_list(list);
  free_list(&list);
}
