#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

int main()
{
    int sockfd, connfd;
    char buffer[1024];

    struct sockaddr_in servaddr, cliaddr;
    socklen_t len = sizeof(cliaddr);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(sockfd < 0)
    {
        printf("Socket creation failed\n");
        return 1;
    }

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(8080);

    if(bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        printf("Bind failed\n");
        close(sockfd);
        return 1;
    }

    if(listen(sockfd, 5) < 0)
    {
        printf("Listen failed\n");
        close(sockfd);
        return 1;
    }

    printf("TCP Server is waiting for connection...\n");

    connfd = accept(sockfd, (struct sockaddr *)&cliaddr, &len);

    if(connfd < 0)
    {
        printf("Connection failed\n");
        close(sockfd);
        return 1;
    }

    printf("Client connected successfully\n");

    while(1)
    {
        memset(buffer, 0, sizeof(buffer));

        int iBytes = recv(connfd, buffer, sizeof(buffer) - 1, 0);

        if(iBytes <= 0)
        {
            printf("Client disconnected\n");
            break;
        }

        buffer[iBytes] = '\0';

        printf("Client: %s\n", buffer);

        if(strcmp(buffer, "exit") == 0)
            break;

        printf("Server: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        send(connfd, buffer, strlen(buffer), 0);

        if(strcmp(buffer, "exit") == 0)
            break;
    }

    close(connfd);
    close(sockfd);

    return 0;
}
