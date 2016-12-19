#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "request.h"

void check_error(int bytes, int client_sock){
  if(bytes < 0){
        printf("\nOpss! Network has some error!\n");
        close(client_sock);
        exit(-1);
  }
}


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
      return protocol->message;
    } else {
      printf("Khong duoc phep\n");
    }
  } while (protocol->message != ALLOW_PLAY);
}


void ready(Protocol* protocol, User* user, int client_sock, int state){
  int bytes_sent;
  assign_user(protocol, user, state);
  protocol->message = I_AM_READY;
  bytes_sent = send(client_sock, protocol, sizeof(Protocol), 0);
  check_error(bytes_sent, client_sock);
}
