#include "pipe_networking.h"
//ACK and HANDSHAKE_BUFFER_SIZE found in pipe_networking.h

/*=========================
  server_handshake
  args: int * to_client
  Perofrms the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.
  returns the file descriptor for the upstream pipe.
  =========================*/


  //define the wellknown pipe
  #ifndef WELLKNOWN
  #define WELLKNOWN "wellknown"
  #endif
int server_handshake(int *to_client) {
  char buf[HANDSHAKE_BUFFER_SIZE];
  //make fif0 (wellkown) with permissions 0644
  mkfifo(WELLKNOWN , 0644);
  printf("Wellknown fifo created. \n");

  int client2server = open(WELLKNOWN, O_RDONLY);
  read(client2server , buf, sizeof(buf));
  printf("Line received : %s \n", buf);
//remove the fifo
  remove(WELLKNOWN);

  *to_client = open(buf, O_WRONLY);//setting to_client  = fd of downstreampipe

  strncpy(buf, ACK, strlen(ACK));
  write(*to_client, buf, sizeof(buf));

  read(client2server, buf, sizeof(buf));
  printf("Confirmation : %s\n", buf);
  //if the string is the same as the acknownledgement string then the connection was sucessful
  if(!strcmp(buf, ACK)){
    printf("connection made\n");
  }
  return client2server;
}


/*=========================
  client_handshake
  args: int * to_server
  Perofrms the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.
  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  char buf[HANDSHAKE_BUFFER_SIZE]; //buff
  char p_name[HANDSHAKE_BUFFER_SIZE]; //pipe_name

  sprintf(p_name, "%d", getpid());
  strncpy(buf, p_name, sizeof("p_name"));
  mkfifo(p_name, 0644); //make fifo with pname and 0644 permissions
  printf("Pipe %s has connected\n" , p_name);

  *to_server = open(WELLKNOWN , O_WRONLY); //setting to_server = fd for upstream pipe
  printf("connecting to WELLKNOWN");
  write(*to_server, buf, sizeof(buf));

  int server2client = open (WELLKNOWN , O_RDONLY);
  read(server2client, buf, sizeof(buf));
  printf("Message received : %s\n", buf);

  if(!strcmp(buf,ACK)){
    printf("handshooken\n");
  }
  remove(p_name);

  return server2client;
}
