#include <stdio.h>
#include <stdlib.h>

int main()
{
   int i, n, size, rate, current=0;
   int packet[100];

   printf("Enter bucket size: ");
   scanf("%d", &size);
   printf("Enter output rate: ");
   scanf("%d", &rate);
   printf("Enter no. of packets: ");
   scanf("%d", &n);
   printf("Enter packet sizes: ");
   for(i=0;i<n;i++)
      scanf("%d",&packet[i]);

   printf("Time\tPacketSize\tBucketContent\tOutput\tDropped\tRemaining\n");

   for(i=0;i<n;i++)
   {
       int dropped=0;
       if(current+packet[i]<=size)
           current += packet[i];
       else
       {
          dropped = packet[i];
       }
       int sent;
       if(current >= rate)
       {
          sent = rate;
          current -= rate;
       }
       else
       {
          sent= current;
          current = 0;
       }
       printf("%d\t%d\t\t%d\t\t%d\t%d\t%d\n",i+1,packet[i],current+sent,sent,dropped,current);
   }
   return 0;

}
