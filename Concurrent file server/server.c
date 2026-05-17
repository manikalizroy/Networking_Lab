#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define PORT 1234

int main()
{
    int server_fd, new_socket;

    struct sockaddr_in address;

    char file[100], buffer[1024];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));

    listen(server_fd, 5);

    printf("Waiting for client...\n");

    new_socket = accept(server_fd, NULL, NULL);

    printf("Client connected!\n");

    recv(new_socket, file, sizeof(file), 0);

    printf("Requested file: %s\n", file);

    FILE *fp = fopen(file, "r");

    if(fp == NULL)
    {
        strcpy(buffer, "File does not exist");
    }
    else
    {
        fread(buffer, 1, sizeof(buffer), fp);

        fclose(fp);
    }

    send(new_socket, buffer, strlen(buffer)+1, 0);

    printf("File content sent\n");

    close(new_socket);
    close(server_fd);

    return 0;
}
