#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "play.h"

void check_file_exist(FILE *f){
  if (f==NULL){
    printf("FILE NOT FOUND!\n");
    exit(-1);
  }
}

int allow_play(Protocol* protocol, User* top_user, Room** top_room){
  User* u;
  u = search_user(top_user, protocol->user_info.name);
  if (u == NULL){
    return 0;
  }
  if (u->state != protocol->state){
    return 0;
  }
  Room* p=NULL;
  p = is_first_user_in_room(*top_room, u->name);
  //Neu user da o trong 1 room 
  //neu room do full thi cho phep choi
  //neu chua full tiep tuc cho
  if (p!=NULL){
    if (room_full(p)){
      u->state = READY;
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

void response_request_play(int client, Protocol* protocol, int allow){
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
  check_error(bytes_sent, client);
}



void show_question(Protocol* protocol, User* top_user, Room* top_room, int client){

  User* u;
  u = search_user(top_user, protocol->user_info.name);
  if (u == NULL){
    return 0;
  }
  if (u->state != protocol->state){
    return 0;
  }

  Room* room;
  room = in_room(top_room, u->name);
  if (room == NULL){
    return 0;
  }

  protocol->state = PLAYING;
  protocol->message = QUESTION;

  char ques_file_name[30];
  char sug[30];
  char ques_image_name[30];
  char s[30];
  strcpy(s, "");
  strcat(s, "question/");

  sprintf(ques_file_name, "%d", room->question_number);
  strcat(ques_file_name, ".dat");
  strcat(s, ques_file_name);
  strcpy(ques_file_name, s);

  FILE *ques_file = fopen(ques_file_name, "r");
  check_file_exist(ques_file);
  fscanf(ques_file, "%s", sug);

  strcpy(protocol->question.suggestion, sug);
  fclose(ques_file);

  sprintf(ques_image_name, "%d", room->question_number);
  strcat(ques_image_name, ".jpg");
  strcpy(s, "");
  strcat(s, "question/");
  strcat(s, ques_image_name);
  strcpy(ques_image_name, s);

  FILE *ques_image = fopen(ques_image_name, "rb");
  check_file_exist(ques_image);

  fseek(ques_image, 0, SEEK_END);
  protocol->question.image_size = ftell(ques_image);
  fclose(ques_image);

  int bytes_sent;
  bytes_sent = send(client, protocol, sizeof(Protocol), 0);
  check_error(bytes_sent, client);

  u->state = PLAYING;
}


void send_image(Protocol* protocol, User* top_user, Room* top_room, int client){

  User* u;
  u = search_user(top_user, protocol->user_info.name);
  if (u == NULL){
    return 0;
  }
  if (u->state != protocol->state){
    return 0;
  }

  Room* room;
  room = in_room(top_room, u->name);
  if (room == NULL){
    return 0;
  }

  char ques_image_name[30];
  char s[30];
  char buff[1024];
  int bytes_sent;

  strcpy(s, "");
  strcat(s, "question/");

  sprintf(ques_image_name, "%d", room->question_number);
  strcat(ques_image_name, ".jpg");
  strcat(s, ques_image_name);
  strcpy(ques_image_name, s);

  FILE *ques_image = fopen(ques_image_name, "rb");
  check_file_exist(ques_image);

  fseek(ques_image, 0, SEEK_END);
  int image_size = ftell(ques_image);


  while (fread(buff, 1, 1024, ques_image) != 0){
    bytes_sent = send(client, buff, 1024, 0);
    check_error(bytes_sent, client);
  }
  
  fclose(ques_image);
}
