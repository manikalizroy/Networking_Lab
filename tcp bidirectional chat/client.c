#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int sock;
    struct sockaddr_in serv_addr;
    char msg[1024], buffer[1024];

    sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(9090);
    inet_pton(AF_INET,"127.0.0.1", &serv_addr.sin_addr);

    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    printf("Connection established..\n");
    while(1)
    {
        //msg to server
        printf("You: ");
        memset(msg, sizeof(msg), 0);
        fgets(msg, sizeof(msg), stdin);
        send(sock, msg, strlen(msg),0);

        if(strncmp(msg, "exit", 4)==0)
           break;

        //msg from server
        memset(buffer, sizeof(buffer), 0);
        read(sock, buffer, sizeof(buffer));

        if(strncmp(buffer, "exit", 4)==0)
           break;

        printf("Server: %s", buffer);
    }
    printf("Chat ended!!\n");
    close(sock);
    return 0;
}
