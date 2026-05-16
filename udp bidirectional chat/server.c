#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[1024], message[1024];
    socklen_t len = sizeof(client_addr);

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));

    printf("UDP Server waiting...\n");

    while(1) {
        // Receive from client
        recvfrom(sockfd, buffer, sizeof(buffer), 0,
                 (struct sockaddr*)&client_addr, &len);

        printf("Client: %s", buffer);

        if(strncmp(buffer, "exit", 4) == 0)
            break;

        // Send reply
        printf("Server: ");
        fgets(message, sizeof(message), stdin);

        sendto(sockfd, message, strlen(message), 0,
               (struct sockaddr*)&client_addr, len);

        if(strncmp(message, "exit", 4) == 0)
            break;
    }

    close(sockfd);
    return 0;
}
