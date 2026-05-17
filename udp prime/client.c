#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
   int sockfd,n;
   struct sockaddr_in serv_addr;
   socklen_t len = sizeof(serv_addr);

   sockfd = socket(AF_INET, SOCK_DGRAM, 0);

   serv_addr.sin_family = AF_INET;
   serv_addr.sin_port = htons(8228);
   inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

   printf("Client socket created\n");

   printf("Enter a number: ");
   scanf("%d",&n);

   sendto(sockfd, &n, sizeof(n), 0, (struct sockaddr*)&serv_addr, len);
   char buffer[1024];

   memset(buffer, 0, sizeof(buffer));
   recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&serv_addr, &len);

   printf("%s\n", buffer);
   close(sockfd);
   return 0;

}
