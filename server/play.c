#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "play.h"


int request_play(Protocol* protocol, User* top_user, Room** top_room){
  User* u;
  u = search_user(top_user, protocol->user_info.name);
  if (u == NULL){
    return 0;
  }
  if (u->state != protocol->state){
    return 0;
  }
  Room* p=NULL;
  p = in_room(*top_room, u->name);
  //Neu user da o trong 1 room 
  //neu room do full thi cho phep choi
  //neu chua full tiep tuc cho
  if (p!=NULL){
    if (room_full(p)){
      return 1;
    } else {
      return 0;
    }
  }


  //Neu cac room da day, tao room moi
  //add nguoi nay vao, cho den khi du 2 nguoi
  if (room_full(*top_room)){
    add_to_head_room_list(top_room, make_room());
    join_room(*top_room, u);
    return 0;
  } else {
    //Co room thieu 1 nguoi, add vao va choi luon
    u->state = READY;
    join_room(*top_room, u);
    return 1;
  }

}

int allow_play(int client, Protocol* protocol, int allow){
  int bytes_sent;
  if (allow){
    protocol->state = READY;
    protocol->message = ALLOW_PLAY;
    bytes_sent = send(client, protocol, sizeof(Protocol), 0);
  } else {
    protocol->state = AUTHENTICATE;
    protocol->message = NOT_ALLOW_PLAY;
    bytes_sent = send(client, protocol, sizeof(Protocol), 0);
  }
  return bytes_sent;
}
