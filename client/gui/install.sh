# !bin/bash
gcc -Wall -g login.c -o login `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`  -w && ./login
