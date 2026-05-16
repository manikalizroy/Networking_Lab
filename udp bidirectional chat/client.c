#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[1024], message[1024];
    socklen_t len = sizeof(server_addr);

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    while(1) {
        // Send message
        printf("You: ");
        fgets(message, sizeof(message), stdin);

        sendto(sockfd, message, strlen(message), 0,
               (struct sockaddr*)&server_addr, len);

        if(strncmp(message, "exit", 4) == 0)
            break;

        // Receive reply
        recvfrom(sockfd, buffer, sizeof(buffer), 0, NULL, NULL);

        printf("Server: %s", buffer);

        if(strncmp(buffer, "exit", 4) == 0)
            break;
    }

    close(sockfd);
    return 0;
}
