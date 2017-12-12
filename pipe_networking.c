#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client

  Perofrms the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  mkfifo("wellknown" , 0644);
  int writefd = open("wellknown" , O_WRONLY);
  int readfd = open("private " , o_RDONLY);
  return 0;
}


/*=========================
  client_handshake
  args: int * to_server

  Perofrms the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  mkfifo("private" , 0644);
  int writefd = open("private" , O_WRONLY);
  int readfd = open("wellknown" , O_RDONLY);
  return 0;
}
