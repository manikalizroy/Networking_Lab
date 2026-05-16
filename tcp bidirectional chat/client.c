#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
   int sock;
   struct sockaddr_in serv_addr;
   char msg[1000], buffer[1000];

   sock = socket(AF_INET, SOCK_STREAM,0);

   serv_addr.sin_family = AF_INET;
   serv_addr.sin_port = htons(8181);
   inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr);

   connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

   printf("Connection established...\n");

   while(1)
   {
      printf("Client: ");
      fgets(buffer, sizeof(buffer), stdin);
      send(sock, buffer, strlen(buffer), 0);

      if(strncmp(buffer, "exit", 4)==0)
        break;

      memset(msg, 0, sizeof(msg));
      read(sock, msg, sizeof(msg));

      if (strncmp(msg, "exit", 4) == 0)
            break;

      printf("Server: %s", msg);
   }
   printf("Chat ended.Client Exiting..\n");
   close(sock);
   return 0;
}
