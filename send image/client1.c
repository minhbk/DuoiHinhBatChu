#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main(){
  int client_sock;
  char buff[1024];
  struct sockaddr_in server_addr;
  int bytes_sent,bytes_received, sin_size;

  client_sock=socket(AF_INET,SOCK_STREAM,0);

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(5501);
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  sin_size = sizeof(struct sockaddr);

  if(connect(client_sock,(struct sockaddr*)&server_addr,sizeof(struct sockaddr))!=0){
    printf("\nError!Can not connect to sever!Client exit imediately! ");
    return 0;
  }















  bytes_sent = send(client_sock, "OK", 2, 0);
  if(bytes_sent < 0){
        printf("\nError!Cannot send data to sever!\n");
        close(client_sock);
        exit(-1);
  }

  int file_size;
  bytes_received = recv(client_sock, &file_size, sizeof(int), 0);
  if(bytes_received < 0){
        printf("\nError!Cannot receive data from sever!\n");
        close(client_sock);
        exit(-1);
  }

  FILE *image = fopen("client.jpg", "wb");
  int remain = file_size;

  while (remain > 0){
    bytes_received = recv(client_sock, buff, 1024, 0);
    if(bytes_received < 0){
          printf("\nError!Cannot receive data from sever!\n");
          close(client_sock);
          exit(-1);
    }

    remain -= bytes_received;

    fwrite(buff, 1, 1024, image);

    /* send(client_sock, "OK", 2, 0); */
  }

  fclose(image);

  close(client_sock);
  return 0;
}
