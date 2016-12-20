#ifndef PLAY_H
#define PLAY_H

#include "room.h"
#include "../lib/account.h"
#include "../lib/protocol.h"

#define SCORE_PER_QUESTION 1
#define TOTAL_QUESTION 10

void check_file_exist(FILE *f);

int allow_play(Protocol* protocol, User* top_user, Room** top_room);

void do_sign_up(Protocol* protocol, User** top_user, int client);

void do_sign_in(Protocol* protocol, User* top_user, int client);

void response_request_play(int client, Protocol* protocol, int allow);

int before_show_question(Protocol* protocol, User* top_user, Room* top_room, int client);

void show_question(Protocol* protocol, User* top_user, Room* top_room, int client);

void send_image(Protocol* protocol, User* top_user, Room* top_room, int client);

void check_answer(Protocol* protocol, User* top_user, Room* top_room, int client);

void not_show_question(Protocol* protocol, int client);

void send_result(Protocol* protocol, Room** top_room, User* top_user, int client);
#endif
