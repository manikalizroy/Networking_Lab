#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
   int server_fd,new_sock;
   struct sockaddr_in address;
   char msg[1000], buffer[1000];

   server_fd = socket(AF_INET, SOCK_STREAM,0);

   address.sin_family = AF_INET;
   address.sin_port = htons(8181);
   address.sin_addr.s_addr = INADDR_ANY;

   bind(server_fd, (struct sockaddr*)&address, sizeof(address));
   listen(server_fd,3);

   printf("Server listening..\n");
   new_sock = accept(server_fd, NULL, NULL);

   while(1)
   {
      memset(buffer, 0, sizeof(buffer));
      read(new_sock, buffer, sizeof(buffer));

      if(strncmp(buffer, "exit", 4)==0)
        break;

      printf("Client: %s", buffer);

      printf("Server: ");
      fgets(msg, sizeof(msg), stdin);
      send(new_sock, msg, strlen(msg), 0);

      if(strncmp(msg, "exit", 4)==0)
        break;

   }
   printf("Chat ended.Server Exiting..\n");
   close(new_sock);
   close(server_fd);
   return 0;
}
