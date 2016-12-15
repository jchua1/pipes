#include "pipe_networking.h"

int client_handshake(int * pointer) {

}

int server_handshake(int * pointer) {
  mkfifo("wkp", 0644);
  
}
