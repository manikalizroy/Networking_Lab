#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define PORT 1234

int main()
{
    int sock;

    struct sockaddr_in serv_addr;

    char file[100], buffer[1024];

    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    printf("Enter filename: ");

    scanf("%s", file);

    send(sock, file, strlen(file)+1, 0);

    recv(sock, buffer, sizeof(buffer), 0);

    printf("Server Response:\n%s\n", buffer);

    close(sock);

    return 0;
}
