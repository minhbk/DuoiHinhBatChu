#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/wait.h>
#include "../lib/account.h"
#include "../lib/protocol.h"
#include "play.h"
#include "room.h"
/* #include "question.h" */

#define PORT 5504
#define BACKLOG 20


int main(){

  User* list_user;
  list_user = load_data(account_file);
  Room* list_room; 
  list_room = NULL;

  int listenfd,conn_sock; /* file descriptors */
  struct sockaddr_in server; /* server's address information */
  struct sockaddr_in client; /* client's address information */


  if ((listenfd=socket(PF_INET, SOCK_STREAM, 0)) == -1 ){  /* calls socket() */
    printf("socket() error\n");
    exit(-1);
  }
  bzero(&server, sizeof(server));
  server.sin_family = AF_INET;
  server.sin_port = htons(PORT);   /* Remember htons() from "Conversions" section? =) */
  server.sin_addr.s_addr = htonl(INADDR_ANY);  /* INADDR_ANY puts your IP address automatically */

  if(bind(listenfd,(struct sockaddr*)&server,sizeof(server))==-1){ /* calls bind() */
    printf("bind() error\n");
    exit(-1);
  }

  if(listen(listenfd,BACKLOG) == -1){  /* calls listen() */
    printf("listen() error\n");
    exit(-1);
  }
  int bytes_sent, bytes_received;
  char recv_data[1024];
  char buff[1024];
  int sin_size;
  fd_set readfds;
  fd_set sockfds;
  fd_set writefds;

  int clients[FD_SETSIZE];
  int i;
  int maxfd = listenfd;

  for( i =0; i <FD_SETSIZE;i++){
    clients[i] = -1;
  }
  FD_ZERO(&readfds);
  FD_ZERO(&sockfds);

  FD_SET(listenfd,&sockfds);
  //FD_SET(listenfd,&writefds);

  int nEvents;
  sin_size = sizeof(struct sockaddr_in);
  while(1){
    readfds = sockfds;
    nEvents = select(maxfd+1, &readfds,NULL,NULL,NULL);
    if(nEvents < 0){
      printf("Error events < 0\n");
      exit(0);
    }
    if(FD_ISSET(listenfd,&readfds) != 0){
      conn_sock = accept(listenfd,(struct sockaddr*)&client,&sin_size);
      for(i =0;i <FD_SETSIZE; i++){
        if(clients[i] == -1)
          break;
      }
      if( i == FD_SETSIZE){
        printf("Max connection reached!\n");
        continue;
      } else{
        clients[i] = conn_sock;
        if(conn_sock > maxfd){
          maxfd = conn_sock;
        }
        FD_SET(conn_sock,&sockfds);
      }
      nEvents--;
    }

    for(i = 0;i<FD_SETSIZE; i++){

      if(FD_ISSET(clients[i],&readfds) !=0){
        printf("You got a connection from %s\n",inet_ntoa(client.sin_addr) ); /* prints client's IP */
        Protocol *protocol;
        protocol = (Protocol*)malloc(sizeof(Protocol));

        bytes_received = recv(clients[i], protocol, sizeof(Protocol), 0);
        check_error(bytes_received, clients[i]);
        
        printf("\n\nUser: %s\n", protocol->user_info.name);

        switch(protocol->state){
          case CONNECTED:
            if (protocol->message == WANT_TO_SIGUP){
              do_sign_up(protocol, &list_user, clients[i]);
            } else if (protocol->message == WANT_TO_SIGIN){
              do_sign_in(protocol, list_user, clients[i]);
            }
            break;

          case AUTHENTICATE:
            if (allow_play(protocol, list_user, &list_room)){
              response_request_play(clients[i], protocol, 1);
              printf("Allow play!\n");

            } else {
              response_request_play(clients[i], protocol, 0);

              printf("Deny play!\n");
            }
            break;
          case READY:
            puts("Send question");
            show_question(protocol, list_user, list_room, clients[i]);
            puts("Complete send question");

            break;
          case PLAYING:
            if (protocol->message == REQUEST_IMAGE){
              puts("gui anh");
              send_image(protocol, list_user, list_room, clients[i]);
              puts("xong gui anh");

            }
            //TODO
            close(clients[i]);
            FD_CLR(clients[i],&sockfds);
            clients[i]=-1;
            break;
        }




      }
    }
  }
  close(listenfd);
  return 1;
}
