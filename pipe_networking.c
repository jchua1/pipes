#include "pipe_networking.h"

int client_handshake(int * to_server) {
  //3) Client creates a "private" FIFO
  char private_pipe[100];
  sprintf(private_pipe, "%d", getpid());
  mkfifo(private_pipe, 0644);
  printf("[CLIENT] %s created\n", private_pipe);

  //4) Client connects to server and sends the private FIFO name
  *to_server = open("WKP", O_WRONLY);
  printf("[CLIENT] Connected to WKP\n");
  
  write(*to_server, private_pipe, 100);
  sleep(1);
  printf("[CLIENT] Sent: %s\n", private_pipe);

  //5) Client waits for a message from the server
  int from_server = open(private_pipe, O_RDONLY);
  printf("[CLIENT] Connected to %s\n", private_pipe);

  //8) Client receives server's message, removes its private FIFO
  char message[MESSAGE_BUFFER_SIZE];
  read(from_server, message, MESSAGE_BUFFER_SIZE);
  sleep(2);
  printf("[CLIENT] Received: %s\n", message);
  
  remove(private_pipe);
  sleep(1);
  printf("[CLIENT] %s removed\n", private_pipe);

  //9) Client sends message back to server
  strcpy(message, "Acknowledgement received");
  write(*to_server, message, MESSAGE_BUFFER_SIZE);
  sleep(1);
  printf("[CLIENT] Sent: %s\n", message);
  
  return from_server;
}

int server_handshake(int * from_client) {
  //1) Server creates a FIFO (Well Known Pipe)
  mkfifo("WKP", 0644);
  printf("[SERVER] WKP created\n");

  //2) Server waits for a connection
  *from_client = open("WKP", O_RDONLY);
  printf("[SERVER] Connected to WKP\n");

  //6) Server receives client's message and removes the WKP
  char private_pipe[MESSAGE_BUFFER_SIZE];
  read(*from_client, private_pipe, MESSAGE_BUFFER_SIZE);
  sleep(2);
  printf("[SERVER] Received: %s\n", private_pipe);
  
  remove("WKP");
  sleep(1);
  printf("[SERVER] WKP removed\n");

  //7) Server connects to client FIFO, sending an initial acknowledgement message
  int to_client = open(private_pipe, O_WRONLY);
  printf("[SERVER] Connected to %s\n", private_pipe);

  char message[MESSAGE_BUFFER_SIZE];
  strcpy(message, "Your existence is acknowledged");
  write(to_client, message, MESSAGE_BUFFER_SIZE);
  sleep(1);
  printf("[SERVER] Sent: %s\n", message);

  read(*from_client, message, MESSAGE_BUFFER_SIZE);
  sleep(2);
  printf("[SERVER] Received: %s\n", message);
  
  return to_client;
}
