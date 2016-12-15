#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "account.h"
#include "question.h"

#define CONNECTED 100
#define DISCONNECTED 101
#define SIGUP 102
#define UNAUTHENTICATE 103
#define AUTHENTICATE 104
#define READY 105
#define PLAYING 106

#define WANT_TO_SIGUP 200
#define ALLOW_SIGUP 201
#define FAIL_SIGUP 202
#define DONE_SIGUP 203
#define WANT_TO_SIGIN 204
#define ALLOW_SIGIN 205
#define DONE_SIGIN 206
#define FAIL_SIGIN 207
#define WANT_TO_PLAY 208
#define ALLOW_PLAY 209
#define NOT_ALLOW_PLAY 210
#define I_AM_READY 211
#define QUESTION 212
#define ANSWER 213
#define TRUE 214
#define FALSE 215
#define WIN 216
#define LOSE 217
#define WANT_TO_SIGOUT 218
#define ALLOW_SIGOUT 219
#define WANT_TO_DISCONNECT 220
#define ALLOW_DISCONNECT 221

typedef struct protocol{
  int state;
  User user_info;
  Question question;
  int score;
  char answer[20];
  int message;
} Protocol;

#endif
