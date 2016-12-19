#ifndef ROOM_H
#define ROOM_H

#include "../lib/account.h"

typedef struct room{
  User* user[2];
  int score[2];
  int question_number;
  int right_persion;
  struct room* next;
} Room;

int room_full(Room* room);

void join_room(Room* room, User* user);

int is_empty_room_list(Room* top);

Room* make_room();

void add_to_head_room_list(Room** top, Room* new_room);

int room_has_name(Room* room, char* name);

void del_room(Room** top, char *name);

void free_room_list(Room** top);

Room* is_first_user_in_room(Room* top, char* name);

Room* in_room(Room* top, char* name);
#endif
