#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock;
    struct sockaddr_in serv_addr;
    char message[1024];

    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    while (1) {
        printf("You: ");
        fgets(message, sizeof(message), stdin);

        send(sock, message, strlen(message), 0);

        if (strncmp(message, "exit", 4) == 0)
            break;
    }

    close(sock);
    return 0;
}
