#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
   int sockfd;
   struct sockaddr_in serv_addr;
   socklen_t len= sizeof(serv_addr);
   char buffer[100], msg[100];

   sockfd = socket(AF_INET, SOCK_DGRAM, 0);

   serv_addr.sin_family = AF_INET;
   serv_addr.sin_port = htons(8228);
   inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

   printf("Connected to Server!\n");

   strcpy(buffer,"TIME");
   sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*)&serv_addr, len);
   printf("Request sent to server\n");

   recvfrom(sockfd, msg, sizeof(msg), 0,  (struct sockaddr*)&serv_addr, &len);
   printf("Server Time: %s", msg);

   printf("Exiting..\n");
   sendto(sockfd, "exit", strlen("exit"), 0, (struct sockaddr*)&serv_addr, len);

   close(sockfd);
   return 0;
}
