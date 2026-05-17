#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
    int server_fd, new_socket;

    struct sockaddr_in address;

    int matrix[10][10], transpose[10][10];

    int r, c, i, j;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_port = htons(8080);
    address.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));

    listen(server_fd, 1);

    printf("Waiting for client...\n");

    new_socket = accept(server_fd, NULL, NULL);

    printf("Client connected!\n");

    recv(new_socket, &r, sizeof(r), 0);
    recv(new_socket, &c, sizeof(c), 0);

    recv(new_socket, matrix, sizeof(matrix), 0);

    printf("Received Matrix:\n");

    for(i = 0; i < r; i++)
    {
        for(j = 0; j < c; j++)
        {
            printf("%d ", matrix[i][j]);

            transpose[j][i] = matrix[i][j];
        }

        printf("\n");
    }

    send(new_socket, transpose, sizeof(transpose), 0);

    close(new_socket);
    close(server_fd);

    return 0;
}
