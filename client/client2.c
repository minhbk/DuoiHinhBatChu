#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include "../lib/account.h"
#include "../lib/protocol.h"
#include <unistd.h>
#include <time.h>

#define PORT 5502

int main(){
  int client_sock;
  char buff[1024];
  struct sockaddr_in server_addr;
  int bytes_sent,bytes_received, sin_size;

  client_sock=socket(AF_INET,SOCK_STREAM,0);

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  sin_size = sizeof(struct sockaddr);

  if(connect(client_sock,(struct sockaddr*)&server_addr,sizeof(struct sockaddr))!=0){
    printf("\nError!Can not connect to sever!Client exit imediately! ");
    return 0;
  }

  User *user;
  user = (User*)malloc(sizeof(User));
  strcpy(user->name, "anh");
  strcpy(user->pass, "456");
  user->state = AUTHENTICATE;
  user->next = NULL;

  Protocol *protocol;
  protocol = (Protocol*)malloc(sizeof(Protocol));


  do {
    protocol->state = user->state;
    strcpy(protocol->user_info.name, user->name);
    strcpy(protocol->user_info.pass, user->pass);
    protocol->user_info.state = user->state;
    protocol->user_info.next = user->next;
    protocol->message = WANT_TO_PLAY;

    printf("%d\n", protocol->state);
    printf("%d\n", sizeof(Protocol));
    bytes_sent = send(client_sock, protocol, sizeof(Protocol), 0);
    if(bytes_sent < 0){
          printf("\nError!Cannot send data to sever!\n");
          close(client_sock);
          exit(-1);
    }
    bytes_received = recv(client_sock, protocol, sizeof(Protocol), 0);

    if (protocol->message == ALLOW_PLAY){
      printf("Duoc phep choi\n");
    } else {
      printf("Khong duoc phep\n");
    }
  } while (protocol->message != ALLOW_PLAY);



  close(client_sock);
  return 0;
}
