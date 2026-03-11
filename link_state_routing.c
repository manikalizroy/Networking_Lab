#include <stdio.h>
#include <stdlib.h>

int main()
{
   int n,i,j,src,v,min,adj[10][10],dist[10],last[10],flag[10];
   printf("enter the no. of nodes: ");
   scanf("%d",&n);
   printf("enter the distance matrix: ");
   for(i=0;i<n;i++)
   {
      for(j=0;j<n;j++)
      {
         scanf("%d",&adj[i][j]);
         if(adj[i][j] == 0 && i!=j)
            adj[i][j] = 1000;
      }
   }
   printf("enter source vertex: ");
   scanf("%d",&src);

   for(i=0;i<n;i++)
   {
      flag[i]=0;
      dist[i]=adj[src][i];
      last[i]=0;
   }

   flag[src]=1;
   dist[src]=0;
   for(i=0;i<n;i++)
   {
       min=1000;
       for(j=0;j<n;j++)
       {
          if(flag[j] == 0 && dist[j] < min)
          {
             min = dist[j];
             v = j;
          }
       }
       flag[v]=1;
       for(j=0;j<n;j++)
       {
          if(flag[j]==0)
          {
             if(dist[v]+adj[v][j]<dist[j])
             {
                dist[j] = dist[v]+adj[v][j];
                last[j] = v;
             }
          }
       }
   }

   printf("========Routing Table=======\n");
   printf("Node\tDist\tNext\n");
   for(i=0;i<n;i++)
   {
      printf("%d\t%d\t%d\n",i,dist[i],last[i]);
   }
   return 0;
}
