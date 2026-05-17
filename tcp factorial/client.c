  GNU nano 6.2                                                                                                      fact_c.c
#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
   int sock,n;
   struct sockaddr_in serv_addr;

   long long result;

   sock = socket(AF_INET,SOCK_STREAM,0);

   serv_addr.sin_family=AF_INET;
   serv_addr.sin_port=htons(8080);
   inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr);

   connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

   printf("enter a number: ");
   scanf("%d",&n);

   send(sock,&n,sizeof(n),0);

   recv(sock,&result,sizeof(result),0);

   printf("facorial: %lld\n",result);

   return 0;
}
