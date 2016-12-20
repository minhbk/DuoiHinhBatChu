#include <stdlib.h>
#include <string.h>
#include "room.h"

int room_full(Room* room){
  if (room == NULL){
    return 1;
  } else if (room->user[0] && room->user[1]){
    return 1;
  } else {
    return 0;
  }
}

void join_room(Room* room, User* user){
  if (room->user[0] == NULL){
    room->user[0] = user;
  } else if (room->user[1] == NULL){
    room->user[1] = user;
  }
}

int is_empty_room_list(Room* top){
  return (top == NULL);
}

Room* make_room(){
  Room* room = (Room*)malloc(sizeof(Room));
  room->user[0] = NULL;
  room->user[1] = NULL;
  room->score[0] = 0;
  room->score[1] = 0;
  room->question_number = 1;
  room->next = NULL;

  int i;
  for (i=0;i<30;i++){
    room->right_persion[i] = -1;
    /* room->ans_per_count = 0; */
    room->user_answersed[0][i] = 0;
    room->user_answersed[1][i] = 0;
  }
  return room;
}


void add_to_head_room_list(Room** top, Room* new_room){
  new_room->next = (*top);
  (*top) = new_room;
}

int room_has_name(Room* room, char* name){
  if (room->user[0] != NULL &&
      room->user[1] != NULL &&
      (strcmp(room->user[0]->name, name) == 0 ||
       strcmp(room->user[1]->name, name) == 0)){
    return 1;
  } else {
    return 0;
  }
}

//chi del dc room khi room do full
void del_room(Room** top, char *name){
  Room* p;
  if (room_has_name(*top, name)){
    p = (*top);
    (*top) = (*top)->next;
    free(p);
  } else {
    for (p=(*top); p->next!=NULL; p=p->next){
    //Neu tim thay room co user ten la name
      if (room_has_name(p->next, name)){
        Room* temp;
        temp = p->next;
        p->next = temp->next;
        free(temp);
        break;
      }
    }
  }
}

void free_room_list(Room** top){
  Room* room;
  while (!is_empty_room_list(*top)){
    room = (*top);
    (*top) = room->next;
    free(room);
  }
  (*top) = NULL;
}

//Do cac phong moi luon dc add vao dau
//Mot user AUTHENTICATE neu da vao room
//thi chac chan o room dau tien (top)
//Neu o room thu 2 thi room 2 da day
//nen no se co trang thai READY hoac PLAYING
/* int in_room(Room* top, char* name){ */
/*   Room* p; */
/*   if (top == NULL){ */
/*     return 0; */
/*   }else if (room_full(top)){ */
/*     return 0; */
/*   } else if (strcmp(top->user1->name, name)==0){ */
/*     return 1; */
/*   } else { */
/*     return 0; */
/*   } */
/* } */


Room* is_first_user_in_room(Room* top, char* name){
  Room* p;
  for (p=top; p!=NULL; p=p->next){
    if (strcmp(p->user[0]->name, name)==0){
      return p;
    } 
  }

  return NULL;
}

Room* in_room(Room* top, char* name){
  Room* p;
  for (p=top; p!=NULL; p=p->next){
    if (strcmp(p->user[0]->name, name)==0){
      return p;
    } else if (strcmp(p->user[1]->name, name)==0){
      return p;
    }
  }
  return NULL;
} 


int position_in_room(Room* room, char* name){
  int i;
  for (i=0; i<=1;i++){
    if (strcmp(room->user[i]->name, name)==0){
      return i;
    }
  }

  return -1;
}


int persion_answ_count(Room* room, int ques_num){
  int count;
  count = 0;
  if (room->user_answersed[0][ques_num]){
    count++;
  }
  if (room->user_answersed[1][ques_num]){
    count++;
  }

  return count;
}
