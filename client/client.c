#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <string.h>
#include <unistd.h>
#include <time.h>

#include "../lib/protocol.h"
#include "../lib/account.h"
#include "request.h"

#define PORT 5502

int main(){
  int client_sock;
  char buff[1024];
  struct sockaddr_in server_addr;
  int bytes_sent,bytes_received, sin_size;
  int state;

  client_sock=socket(AF_INET,SOCK_STREAM,0);

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  sin_size = sizeof(struct sockaddr);

  if(connect(client_sock,(struct sockaddr*)&server_addr,sizeof(struct sockaddr))!=0){
    printf("\nError!Can not connect to sever!Client exit imediately! ");
    return 0;
  }

  //khoi tao trang thai
  state = AUTHENTICATE;

  User *user;
  user = (User*)malloc(sizeof(User));
  printf("Nhap username: "); gets(user->name);
  printf("Nhap pass: "); gets(user->pass);
  user->state = state;
  user->next = NULL;

  Protocol *protocol;
  protocol = (Protocol*)malloc(sizeof(Protocol));


  state = request_play(protocol, user, client_sock, state);
  /* ready(protocol, user, client_sock, state); */
  /* recv_question() */


  close(client_sock);
  return 0;
}
