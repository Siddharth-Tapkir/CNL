
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
    int sockfd;
    char buffer[1024];

    struct sockaddr_in servaddr;
    socklen_t len = sizeof(servaddr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if(sockfd < 0)
    {
        printf("Socket creation failed\n");
        return 1;
    }

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8080);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Enter a string: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';

    sendto(sockfd, buffer, strlen(buffer), 0,
           (struct sockaddr *)&servaddr, sizeof(servaddr));

    int iBytes = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0,
                          (struct sockaddr *)&servaddr, &len);

    if(iBytes < 0)
    {
        printf("Receive failed\n");
        close(sockfd);
        return 1;
    }

    buffer[iBytes] = '\0';

    printf("Reversed String: %s\n", buffer);

    close(sockfd);

    return 0;
}
