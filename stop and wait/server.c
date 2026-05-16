#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <time.h>

int main()
{
   int server_fd, newsock;
   struct sockaddr_in address;
   int ack, frame;

   srand(time(NULL));

   server_fd = socket(AF_INET, SOCK_STREAM, 0);
   address.sin_family = AF_INET;
   address.sin_port = htons(8181);
   address.sin_addr.s_addr = INADDR_ANY;

   bind(server_fd, (struct sockaddr*)&address, sizeof(address));
   listen(server_fd, 5);

   printf("Waiting for client\n");

   newsock = accept(server_fd, NULL, NULL);
   printf("Client connected!!\n");

   while(1)
   {
        recv(newsock, &frame, sizeof(frame),0);
        if(frame == -1)
           break;
        printf("Received frame: %d\n",frame);

        ack = 1-frame;

        int loss = rand()%3;
        if(loss==0)
           printf("ACK lost\n");
        else
        {
           printf("Sending ACK: %d\n---------------------------------\n", ack);
           send(newsock, &ack, sizeof(ack), 0);
        }
   }
   close(newsock);
   close(server_fd);
   return 0;
}
