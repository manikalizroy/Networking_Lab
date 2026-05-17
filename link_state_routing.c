#include <stdio.h>
#include <stdlib.h>
#define INF 999
int main()
{
   int n,i,j,v,src,min,flag[10];
   int cost[10][10],dist[10],last[10];

   printf("enter no. of nodes: ");
   scanf("%d",&n);
   printf("enter the the distance matrix:");
   for(i=0;i<n;i++)
   {
      for(j=0;j<n;j++)
      {
         scanf("%d",&cost[i][j]);
         if(cost[i][j] == 0 && i!=j)
            cost[i][j] = INF;
      }
   }

   printf("enter the source vertex: ");
   scanf("%d",&src);

   for(i=0;i<n;i++)
   {
      flag[i]=0;
      dist[i] = cost[src][i];
      last[i]=src;
   }
   last[src] = src;
   flag[src] = 1;
   dist[src] = 0;

   for(i=0;i<n;i++)
   {
      min = INF;
      v = -1;
      for(j=0;j<n;j++)
      {
         if(flag[j] == 0 && dist[j] < min)
         {
            min = dist[j];
            v = j;
         }
      }

      if(v == -1)
         break;

     flag[v] = 1;
     for(j=0;j<n;j++)
     {
        if(flag[j] == 0)
        {
           if(dist[v] + cost[v][j] < dist[j])
           {
              dist[j] = dist[v] + cost[v][j];
              last[j] = v;
           }
        }
     }
   }

   printf("======Routing Table======\n");
   printf("Node\tDist\tPrevious\n");
   for(i=0;i<n;i++)
   {
      printf("%d\t%d\t%d\n",i,dist[i],last[i]);
   }

   return 0;
}
