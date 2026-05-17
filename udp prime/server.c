#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>

int isprime(int n)
{
        if(n<=0)
        {
                return 0;
        }
        for(int i=2;i*i<=n;i++)
        {
                if(n%i==0)
                        return 0;
        }
        return 1;
}

int main()
{
        int sock,n;
        struct sockaddr_in server_addr,client_addr;
        socklen_t addr_len=sizeof(client_addr);
        char buffer[1024];
        int bytes;

        sock=socket(AF_INET,SOCK_DGRAM,0);

        server_addr.sin_family=AF_INET;
        server_addr.sin_port=htons(8080);
        server_addr.sin_addr.s_addr=INADDR_ANY;

        bind(sock,(struct sockaddr*)&server_addr,sizeof(server_addr));
        printf("server waiting for connection\n");

        //memset(buffer,0,sizeof(buffer));
        bytes=recvfrom(sock,&n,sizeof(n),0,(struct sockaddr*)&client_addr,&addr_len);
        printf("Received number:%d\n",n);

        memset(buffer,0,sizeof(buffer));

        if(isprime(n))
        {
                sprintf(buffer,"Number is prime.Factors are 1,%d\n",n);
        }
        else
        {
                sprintf(buffer,"Number is composite.Factors are ");
                for(int i=1;i<=n;i++)
                {
                        if(n%i==0)
                        {
                                char temp[20];
                                sprintf(temp,"%d,",i);
                                strcat(buffer,temp);
                        }
                }
        }

        sendto(sock,buffer,sizeof(buffer)-1,0,(struct sockaddr*)&client_addr,addr_len);
        close(sock);
        return 0;
}
