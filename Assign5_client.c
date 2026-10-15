#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

int main()
{
    int sockfd;
    char buffer[1024];

    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(sockfd < 0)
    {
        printf("Socket creation failed\n");
        return 1;
    }

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8080);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        printf("Connection failed\n");
        close(sockfd);
        return 1;
    }

    printf("Connected to TCP Server\n");

    while(1)
    {
        printf("Client: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        send(sockfd, buffer, strlen(buffer), 0);

        if(strcmp(buffer, "exit") == 0)
            break;

        memset(buffer, 0, sizeof(buffer));

        int iBytes = recv(sockfd, buffer, sizeof(buffer) - 1, 0);

        if(iBytes <= 0)
        {
            printf("Server disconnected\n");
            break;
        }

        buffer[iBytes] = '\0';

        printf("Server: %s\n", buffer);

        if(strcmp(buffer, "exit") == 0)
            break;
    }

    close(sockfd);

    return 0;
}
