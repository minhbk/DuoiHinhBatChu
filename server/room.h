#ifndef ROOM_H
#define ROOM_H

#include "../lib/account.h"

typedef struct room{
  User* user[2];
  int score[2];
  int question_number;
  //right_persion[i] la nguoi dau tien tra loi dung cau thu i
  int right_persion[30];
  //ans_per_count[i] la so nguoi da tra loi cau thu i
  // int ans_per_count[30];
  
  //user_answersed[i][j] = 0 neu nguoi thu i chua tra loi cau hoi j
  int user_answersed[2][30];
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

int position_in_room(Room* room, char* name);

int persion_answ_count(Room* room, int ques_num);
#endif
