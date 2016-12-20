#ifndef GLOBAL_VARIABLE_H
#define GLOBAL_VARIABLE_H

#include "../lib/account.h"
#include "../lib/protocol.h"


extern int client_sock;
extern struct sockaddr_in server_addr;
extern int state;
extern User* user;
extern Protocol* protocol;

#endif
