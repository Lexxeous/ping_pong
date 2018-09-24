#include "pingpong.h"

int main()
{

  // char* bob = malloc(23); // 
  // int bob_len2 = strlen(bob);  
  // int bob_len1 = (sizeof(bob)/sizeof(bob[0])) - 1;
  // int bob_len3 = sizeof(bob);
  // printf("%d \n",bob_len2);
  // printf("%d \n",bob_len1);
  // printf("%d \n",bob_len3);


  int port = 10001;
  int retries = 100;

  while(retries --)
  {
    if(!run_server(port))
    {
      printf("Server running on port %i.\n", port);
      while(1)
      {
        sleep(10);
      }
    }
    else
    {
      port ++;
    }
  }
  printf("Failed to start server.\n");

  return 1;
}
