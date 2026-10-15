
#include <stdio.h>

#define INF 999

int main()
{
    int cost[10][10], dist[10][10];
    int n, i, j, k, updated;

    printf("Enter number of routers: ");
    scanf("%d", &n);

    printf("Enter cost matrix (999 for no link):\n");

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            scanf("%d", &cost[i][j]);
            dist[i][j] = cost[i][j];
        }
    }

    do
    {
        updated = 0;

        for(i = 0; i < n; i++)
        {
            for(j = 0; j < n; j++)
            {
                for(k = 0; k < n; k++)
                {
                    if(dist[i][j] > cost[i][k] + dist[k][j])
                    {
                        dist[i][j] = cost[i][k] + dist[k][j];
                        updated = 1;
                    }
                }
            }
        }
    } while(updated);

    printf("\nFinal Routing Table:\n");

    for(i = 0; i < n; i++)
    {
        printf("\nRouter %d:\n", i + 1);
        printf("Destination\tCost\n");

        for(j = 0; j < n; j++)
        {
            if(dist[i][j] >= INF)
                printf("%d\t\tINF\n", j + 1);
            else
                printf("%d\t\t%d\n", j + 1, dist[i][j]);
        }
    }

    return 0;
}
 
