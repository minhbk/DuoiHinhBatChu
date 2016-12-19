#ifndef PLAY_H
#define PLAY_H

#include "room.h"
#include "../lib/account.h"
#include "../lib/protocol.h"

void check_file_exist(FILE *f);

int allow_play(Protocol* protocol, User* top_user, Room** top_room);
// void ready_status(Protocol* protocol);

void response_request_play(int client, Protocol* protocol, int allow);

void show_question(Protocol* protocol, User* top_user, Room* top_room, int client);

void send_image(Protocol* protocol, User* top_user, Room* top_room, int client);
#endif
