#include "ping_pong.h"

int main()
{
  int port = 10001; // starting port number
  int retries = 100; // number of retries before failure

  while(retries --) // try to start server 100 times
  {
    if(!run_server(port))
    {
      printf("Server running on port %i.\n", port);
      while(1)
      {
        sleep(10); // number of seconds of wait time before retry
      }
    }
    else
    {
      port ++; // increment port number if failure on previous port
    }
  }
  printf("Failed to start server.\n");

  return 1;
}
