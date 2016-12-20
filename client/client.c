#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <string.h>
#include <unistd.h>

#include "../lib/protocol.h"
#include "../lib/account.h"
#include "request.h"
#include "global_variable.h"

#include "login_ui.h"

#define PORT 5501


int client_sock;
struct sockaddr_in server_addr;
int state;
User* user;
Protocol* protocol;

int main(int argc, char *argv[]){
  char buff[1024];
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

  state = CONNECTED;
  user = (User*)malloc(sizeof(User));
  protocol = (Protocol*)malloc(sizeof(Protocol));


  create_login_ui(argc,argv);


  close(client_sock);
  return 0;
}
