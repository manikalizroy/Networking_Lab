#include <stdio.h>
#include <stdlib.h>

int main()
{
    int size, rate, n, i ,j, current=0;
    int packet[100], dropped[100];

    printf("enter bucket size: ");
    scanf("%d", &size);
    printf("enter output rate: ");
    scanf("%d", &rate);
    printf("enter no. of packets: ");
    scanf("%d", &n);
    printf("enter packet sizes:");
    for(i=0;i<n;i++)
    {
        scanf("%d", &packet[i]);
    }

    printf("Time\tPacket\tBucket\tRate\tDropped\tRem\n");
    printf("0\t-\t-\t0\t-\t-\n");
    for(i=0;i<n;i++)
    {
        int dropped = 0;
        if(current+packet[i]<=size)
            current += packet[i];
        else
        {
            dropped = current+packet[i] - size;
            current = size;
        }
        if(current < rate)
        {
            printf("%d\t%d\t%d\t%d\t%d\t%d\n",i+1,packet[i],current,current,dropped,0);
            current=0;
        }
        else
        {
            printf("%d\t%d\t%d\t%d\t%d\t%d\n",i+1,packet[i],current,rate,dropped,current-rate);
            current -= rate;
        }
    }
    return 0;
}
