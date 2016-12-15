#ifndef ROOM_H
#define ROOM_H

#include "../lib/account.h"

typedef struct room{
  User* user1;
  User* user2;
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

Room* in_room(Room* top, char* name);

#endif
