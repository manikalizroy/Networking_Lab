#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
   int sockfd;
   struct sockaddr_in serv_addr, client_addr;
   socklen_t len= sizeof(client_addr);
   time_t c_time;
   char buffer[100];

   sockfd = socket(AF_INET, SOCK_DGRAM, 0);

   serv_addr.sin_family = AF_INET;
   serv_addr.sin_port = htons(8228);
   serv_addr.sin_addr.s_addr = INADDR_ANY;

   bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

   printf("Server socket created\n");

   while(1)
   {
      memset(buffer, 0, sizeof(buffer));
      recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&client_addr, &len);
      printf("Client request: %s\n", buffer);

      if(strncmp(buffer, "exit", 4) == 0)
      {
         printf("Exiting..\n");
         break;
      }
      c_time = time(NULL);
      strcpy(buffer, ctime(&c_time));

      sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*)&client_addr, len);
      printf("Time send to client\n");
   }
   close(sockfd);
   return 0;
}
