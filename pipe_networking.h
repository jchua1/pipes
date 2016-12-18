#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MESSAGE_BUFFER_SIZE 100

int client_handshake(int * to_server);

int server_handshake(int * from_client);
