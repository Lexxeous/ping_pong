#include "ping_pong.h"

const int CLI_BUF_LEN = 4096; // global variable to allocate different amounts of chars

int main(int argc, char* argv[])
{
  int port = atoi(argv[1]); // ACSII to integer

  // error check the terminal command
  if(argc < 2)
  {
    printf("Give port as command line argument.\n");
    return 1;
  }

  ConnectionInfo info;
  if(connect_to_server("localhost", port, &info))
  {
    printf("Failed to connect to server.\n");
    return 1;
  }

  while(1)
  {
    char buff[CLI_BUF_LEN];

    // read a string
    printf("Gimme a string:\n");
    fgets(buff, CLI_BUF_LEN, stdin);

    int len = strlen(buff);
    buff[len-1]=0; // -1 to remove trailing '\n'

    // send the string
    sendMessage(&info, buff);

    // receive the string
    char* msg = receiveMessage(&info);

    if(msg == NULL)
    {
      printf("Failed to receive message.\n");
      return 1;
    }

    printf("%s\n", msg); // print the server response message
    dealocate_message(msg); // free (deallocate) message memory
  }

  return 2; // shouldn't ever run
}
