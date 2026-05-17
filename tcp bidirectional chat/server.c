#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int server_fd, newsock;
    struct sockaddr_in address;
    char buffer[1024], msg[1024];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_port = htons(9090);
    address.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd,3);

    printf("Waiting for client..\n");
    newsock = accept(server_fd, NULL, NULL);


    while(1)
    {
        //msg from client
        memset(buffer, 0, sizeof(buffer));
        read(newsock, buffer, sizeof(buffer));

        if(strncmp(buffer, "exit", 4)==0)
            break;
        printf("Client: %s\n",buffer);

        //msg to client
        memset(msg, 0, sizeof(msg));
        printf("You: ");
        fgets(msg, sizeof(msg),stdin);
        send(newsock, msg, strlen(msg),0);

        if(strncmp(msg, "exit", 4)==0)
            break;
    }

    printf("Chat ended!!\n");
    close(newsock);
    close(server_fd);
    return 0;
}
