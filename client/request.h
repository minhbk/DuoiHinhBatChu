#ifndef REQUEST_H
#define REQUEST_H

#include "../lib/protocol.h"
#include "../lib/account.h"


void assign_user(Protocol* protocol, User* user, int state);

int request_play(Protocol* protocol, User* user, int client_sock, int state);

void ready(Protocol* protocol, User* user, int client_sock, int state);

int request_signup(Protocol* protocol, User* user, int client_sock, int state);

int request_sign_in(Protocol* protocol, User* user, int client_sock, int state);  

void recv_image(char* image_name, int image_size, int client_sock);
#endif
