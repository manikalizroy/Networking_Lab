#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
    int sock;

    struct sockaddr_in serv_addr;

    int matrix[10][10], transpose[10][10];

    int r, c, i, j;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);

    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    printf("Enter rows and columns: ");
    scanf("%d%d", &r, &c);

    printf("Enter matrix elements:\n");

    for(i = 0; i < r; i++)
    {
        for(j = 0; j < c; j++)
        {
            scanf("%d", &matrix[i][j]);
        }
    }

    send(sock, &r, sizeof(r), 0);
    send(sock, &c, sizeof(c), 0);

    send(sock, matrix, sizeof(matrix), 0);

    recv(sock, transpose, sizeof(transpose), 0);

    printf("Transpose Matrix:\n");

    for(i = 0; i < c; i++)
    {
        for(j = 0; j < r; j++)
        {
            printf("%d ", transpose[i][j]);
        }

        printf("\n");
    }

    close(sock);

    return 0;
}
