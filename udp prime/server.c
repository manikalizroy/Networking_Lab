#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int isprime(int n)
{
   int i;
   if (n==1)
       return 0;
   for(i=2;i<=n/2;i++)
   {
       if(n%i == 0)
           return 0;
   }
   return 1;
}

int main()
{
   int sockfd,n;
   struct sockaddr_in serv_addr, client_addr;
   socklen_t len = sizeof(client_addr);

   sockfd = socket(AF_INET, SOCK_DGRAM, 0);

   serv_addr.sin_family = AF_INET;
   serv_addr.sin_port = htons(8228);
   serv_addr.sin_addr.s_addr = INADDR_ANY;

   bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

   recvfrom(sockfd, &n, sizeof(n), 0, (struct sockaddr*)&client_addr, &len);
   printf("Received number: %d\n",n);

   char buffer[100];
   memset(buffer, 0, sizeof(buffer));

   if (isprime(n))
   {
       strcpy(buffer, "It is a prime number");
       sendto(sockfd, buffer, strlen(buffer),  0, (struct sockaddr*)&client_addr, len);
   }
   else
   {
       strcpy(buffer, "It is a composite number");
       sendto(sockfd, buffer, strlen(buffer),  0, (struct sockaddr*)&client_addr, len);
   }

   printf("%s\n", buffer);
   close(sockfd);
   return 0;
}

