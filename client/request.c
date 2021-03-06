#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "request.h"



void assign_user(Protocol* protocol, User* user,int state){
  protocol->state = state;
  strcpy(protocol->user_info.name, user->name);
  strcpy(protocol->user_info.pass, user->pass);
  protocol->user_info.state = state;
  protocol->user_info.next = user->next;
}


int request_play(Protocol* protocol, User* user, int client_sock, int state){
  int bytes_received, bytes_sent;
  do {
    assign_user(protocol, user, state);
    protocol->message = WANT_TO_PLAY;

    bytes_sent = send(client_sock, protocol, sizeof(Protocol), 0);
    check_error(bytes_sent, client_sock);

    bytes_received = recv(client_sock, protocol, sizeof(Protocol), 0);
    check_error(bytes_received, client_sock);

    if (protocol->message == ALLOW_PLAY){
      printf("Duoc phep choi\n");
      return protocol->state;
    } else {
      printf("Khong duoc phep\n");
    }
  } while (protocol->message != ALLOW_PLAY);
}


void ready(Protocol* protocol, User* user, int client_sock, int state){
  int bytes_sent;
  assign_user(protocol, user, state);
  protocol->message = I_AM_READY;
  printf("%d\n", protocol->message);
  printf("%d\n", protocol->state);
  bytes_sent = send(client_sock, protocol, sizeof(Protocol), 0);
  check_error(bytes_sent, client_sock);
}


int request_signup(Protocol* protocol, User* user, int client_sock, int state){
  int bytes_sent, bytes_received;
  assign_user(protocol, user, state);
  protocol->state = state;
  protocol->message = WANT_TO_SIGUP;
  bytes_sent = send(client_sock, protocol, sizeof(Protocol), 0);
  check_error(bytes_sent, client_sock);

  bytes_received = recv(client_sock, protocol, sizeof(Protocol), 0);
  check_error(bytes_received, client_sock);

  if (protocol->message == DONE_SIGUP){
    return 1;
  } else if (protocol->message == FAIL_SIGUP){
    return 0;
  }
}


int request_sign_in(Protocol* protocol, User* user, int client_sock, int state){

  int bytes_sent, bytes_received;
  assign_user(protocol, user, state);
  protocol->state = state;
  protocol->message = WANT_TO_SIGIN;
  bytes_sent = send(client_sock, protocol, sizeof(Protocol), 0);
  check_error(bytes_sent, client_sock);

  bytes_received = recv(client_sock, protocol, sizeof(Protocol), 0);
  check_error(bytes_received, client_sock);

  if (protocol->message == FAIL_SIGIN){
    return 0;
  } else if (protocol->message == DONE_SIGIN){
    return 1;
  }
}


void recv_image(char* image_name, int image_size, int client_sock){

  FILE *image = fopen(image_name, "wb");
  char buff[1024];
  int bytes_received;
  int remain = image_size;
  puts("Bat dau nhan");

  while (remain > 0){
    bytes_received = recv(client_sock, buff, 1024, 0);

    remain = remain - bytes_received;

    fwrite(buff, 1, 1024, image);
  }
  fclose(image);
  puts("Xong nhan anh");
}


void send_answer(Protocol* protocol, User* user, int client_sock, int state, char* answer){

  int bytes_sent;
  assign_user(protocol, user, state);
  protocol->state = state;
  protocol->message = ANSWER;
  strcpy(protocol->answer, answer);

  bytes_sent = send(client_sock, protocol, sizeof(Protocol), 0);
  check_error(bytes_sent, client_sock);
}

void recv_result(Protocol* protocol, User* user, int client_sock){
  int bytes_received = recv(client_sock, protocol, sizeof(Protocol), 0);
  check_error(bytes_received, client_sock);
  if (protocol->message == TRUE){
    puts("Ban da tra loi dung va nhanh nhat");
  } else if (protocol->message == FALSE){
    puts("Ban tra loi sai hoac cham hon");
  }
}


void request_question(Protocol* protocol, User* user, int client_sock, int state){

  int bytes_sent;
  assign_user(protocol, user, state);
  protocol->state = state;
  protocol->message = REQUEST_QUESTION;

  bytes_sent = send(client_sock, protocol, sizeof(Protocol), 0);
  check_error(bytes_sent, client_sock);
}
