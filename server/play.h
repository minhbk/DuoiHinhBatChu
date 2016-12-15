#ifndef PLAY_H
#define PLAY_H

#include "room.h"
#include "../lib/account.h"
#include "../lib/protocol.h"

int reques_play(Protocol* protocol, User* top_user, Room** top_room);
// void ready_status(Protocol* protocol);

int allow_play(int client, Protocol* protocol, int allow);
#endif
