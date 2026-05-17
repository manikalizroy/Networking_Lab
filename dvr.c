#include <stdio.h>
#define INF 999

int main()
{
    int n, i, j, k;
    int cost[10][10], dist[10][10], next[10][10];

    printf("Enter number of routers: ");
    scanf("%d", &n);

    printf("Enter cost matrix (999 for infinity):\n");

    // Input and initialization
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            scanf("%d", &cost[i][j]);
            dist[i][j] = cost[i][j];
            if(cost[i][j] == INF)
                next[i][j] = -1;
            else
                next[i][j] = j;
        }
        dist[i][i] = 0;
        next[i][i] = i;
    }

    // Distance Vector Algorithm (Bellman-Ford)
    // Run n-1 iterations to guarantee convergence
    for(k = 0; k < n - 1; k++)
    {
        // Each router i updates its distance table
        for(i = 0; i < n; i++)
        {
            // Try to relax path to destination j via neighbor v
            for(j = 0; j < n; j++)
            {
                for(int v = 0; v < n; v++)
                {
                    if(cost[i][v] != INF &&
                       dist[v][j] != INF &&
                       dist[i][j] > cost[i][v] + dist[v][j])
                    {
                        dist[i][j] = cost[i][v] + dist[v][j];
                        next[i][j] = v;
                    }
                }
            }
        }
    }

    // Routing table for each router
    for(i = 0; i < n; i++)
    {
        printf("\nRouter %d\n", i);
        printf("Dest\tDist\tNext\n");
        for(j = 0; j < n; j++)
        {
            if(dist[i][j] == INF)
                printf("%d\t INF\t%d\n", j, next[i][j]);
            else
                printf("%d\t%d\t%d\n", j, dist[i][j], next[i][j]);
        }
    }

    // Final Cost Matrix
    printf("\nFinal Cost Matrix:\n\n\t");
    for(i = 0; i < n; i++)
        printf("%d\t", i);
    printf("\n");
    for(i = 0; i < n; i++)
    {
        printf("%d\t", i);
        for(j = 0; j < n; j++)
        {
            if(dist[i][j] == INF)
                printf("INF\t");
            else
                printf("%d\t", dist[i][j]);
        }
        printf("\n");
    }

    return 0;
}
