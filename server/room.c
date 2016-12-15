#include <stdlib.h>
#include <string.h>
#include "room.h"

int room_full(Room* room){
  if (room == NULL){
    return 1;
  } else if (room->user1 && room->user2){
    return 1;
  } else {
    return 0;
  }
}

void join_room(Room* room, User* user){
  if (room->user1 == NULL){
    room->user1 = user;
  } else if (room->user2 == NULL){
    room->user2 = user;
  }
}

int is_empty_room_list(Room* top){
  return (top == NULL);
}

Room* make_room(){
  Room* room = (Room*)malloc(sizeof(Room));
  room->user1 = NULL;
  room->user2 = NULL;
  room->next = NULL;
  return room;
}


void add_to_head_room_list(Room** top, Room* new_room){
  new_room->next = (*top);
  (*top) = new_room;
}

int room_has_name(Room* room, char* name){
  if (room->user1 != NULL &&
      room->user2 != NULL &&
      (strcmp(room->user1->name, name) == 0 ||
       strcmp(room->user2->name, name) == 0)){
    return 1;
  } else {
    return 0;
  }
}
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


Room* in_room(Room* top, char* name){
  Room* p;
  for (p=top; p!=NULL; p=p->next){
    if (strcmp(p->user1->name, name)==0){
      return p;
    }
  }

  return NULL;
}
