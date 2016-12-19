#ifndef REQUEST_H
#define REQUEST_H

#include "../lib/protocol.h"
#include "../lib/account.h"

void check_error(int bytes, int client_sock);

void assign_user(Protocol* protocol, User* user, int state);

int request_play(Protocol* protocol, User* user, int client_sock, int state);

void ready(Protocol* protocol, User* user, int client_sock, int state);

  
#endif
