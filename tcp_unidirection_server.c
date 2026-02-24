#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    char buffer[1024];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_port = htons(8080);
    address.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 3);

    printf("Waiting for client...\n");
    new_socket = accept(server_fd, NULL, NULL);

    while (1) {
        memset(buffer, 0, sizeof(buffer));
        read(new_socket, buffer, sizeof(buffer));

        if (strncmp(buffer, "exit", 4) == 0)
            break;

        printf("Client: %s", buffer);
    }

    printf("Chat ended.\n");

    close(new_socket);
    close(server_fd);
    return 0;
}
