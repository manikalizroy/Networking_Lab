#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>

long long fact(int n)
{
   long long f=1;
   int i;
   if(n==0 || n==1)
        return 1;
   else
   {
      for(i=1;i<=n;i++)
      {
                f = f*i;
      }
   }
   return f;
}

int main()
{
   int server_fd,sock;
   struct sockaddr_in serv_addr,client_addr;
   socklen_t len = sizeof(client_addr);
   int n;
   long long result;

   server_fd = socket(AF_INET,SOCK_STREAM,0);

   serv_addr.sin_family=AF_INET;
   serv_addr.sin_port=htons(8080);
   serv_addr.sin_addr.s_addr=INADDR_ANY;

   bind(server_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
   listen(server_fd,3);

   printf("server waiting..\n");

   sock = accept(server_fd,(struct sockaddr*)&client_addr,&len);

   recv(sock,&n,sizeof(n),0);

   printf("received number: %d\n",n);

   result = fact(n);

   send(sock,&result,sizeof(result),0);

   close(sock);
   close(server_fd);
   return 0;
}
