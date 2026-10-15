
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
    int sockfd;
    char buffer[1024];
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len = sizeof(cliaddr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

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

    printf("UDP Server is waiting for a string...\n");

    int iBytes = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0,
                          (struct sockaddr *)&cliaddr, &len);

    if(iBytes < 0)
    {
        printf("Receive failed\n");
        close(sockfd);
        return 1;
    }

    buffer[iBytes] = '\0';

    printf("Original String: %s\n", buffer);

    int iStart = 0;
    int iEnd = iBytes - 1;

    while(iStart < iEnd)
    {
        char temp = buffer[iStart];
        buffer[iStart] = buffer[iEnd];
        buffer[iEnd] = temp;

        iStart++;
        iEnd--;
    }

    printf("Reversed String: %s\n", buffer);

    sendto(sockfd, buffer, strlen(buffer), 0,
           (struct sockaddr *)&cliaddr, len);

    close(sockfd);

    return 0;
}
