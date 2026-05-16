#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
   int sock;
   struct sockaddr_in serv_addr;
   int ack, seq = 0, total =10, i;

   sock = socket(AF_INET, SOCK_STREAM, 0);

   serv_addr.sin_family = AF_INET;
   serv_addr.sin_port = htons(8181);
   inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

   connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
   printf("Client connected to Server!!\n");

   for(i=0; i<total;)
   {
        printf("Sending frame: %d\n", seq);
        send(sock, &seq, sizeof(seq), 0);

        fd_set readfds;
        struct timeval tv;

        FD_ZERO(&readfds);
        FD_SET(sock, &readfds);
        tv.tv_sec = 3;
        tv.tv_usec = 0;

        int activity = select(sock+1, &readfds, NULL, NULL, &tv);

        if(activity > 0)
        {
           recv(sock, &ack, sizeof(ack), 0);
           printf("Received ACK: %d\n-------------------------\n", ack);

           if(ack == 1-seq)
           {
                printf("Moving to next frame..\n");
                seq = 1-seq;
                i++;
           }
           else
           {
                printf("Wrong ACK! Resending Frame..\n");
           }
        }
        else
        {
           printf("Timeout! Resending Frame...\n");
        }
        sleep(1);
   }
   int end = -1;
   send(sock, &end, sizeof(end), 0);
   close(sock);
   return 0;
}

