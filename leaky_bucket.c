#include <stdio.h>

int main() {
    int bucket_size, output_rate, n;
    int packets[20];
    int i;
    int bucket = 0;

    printf("Enter bucket size: ");
    scanf("%d", &bucket_size);

    printf("Enter output rate: ");
    scanf("%d", &output_rate);

    printf("Enter number of packets: ");
    scanf("%d", &n);

    printf("Enter packet sizes:\n");
    for(i = 0; i < n; i++)
        scanf("%d", &packets[i]);

    printf("\nTime\tPacket\tBucket\tOutput\tDropped\tRemaining\n");

    for(i = 0; i < n; i++) {

        int dropped = 0;

        // Step 1: Add packet
        bucket = bucket + packets[i];

        // Step 2: Check overflow
        if(bucket > bucket_size) {
            dropped = bucket - bucket_size;
            bucket = bucket_size;
        }

        // Store bucket before sending
        int bucket_before = bucket;

        // Step 3: Leak (output)
        int output;
        if(bucket >= output_rate)
            output = output_rate;
        else
            output = bucket;

        bucket = bucket - output;

        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1,
               packets[i],
               bucket_before,
               output,
               dropped,
               bucket);
    }

    return 0;
}

-----------------------------------------------------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

#define OUTGOINGRATE 1
#define BUCKETCAPACITY 10
#define ADD_PACKET 2
    
struct LeakyBucket
{
    int size;
}bucket;


void addPacket(int packetSize)
{
    if(bucket.size + packetSize >= BUCKETCAPACITY)
    {
        printf("Bucket OverFlow!!\n");
        return;
    }
    bucket.size += packetSize;
}


void simulateLeakyBucket(int duration)
{
    int packetSize = 0;
    // add packet at odd intervals and increase the size of the packet by some random amt;
    for(int i = 0; i < duration; i++)
    {
        printf("Time: %d => Bucket Size: %d\n",i,bucket.size);
        if(bucket.size > 0){
            bucket.size -= OUTGOINGRATE;
            if(bucket.size < 0) bucket.size = 0;
        }
        
        if(i%2 == 1)
        {
            packetSize  = packetSize +  ADD_PACKET;
            addPacket(packetSize);
        }
        sleep(1);
    }
}

int main()
{
    int duration = 10;
    bucket.size = 0;
    addPacket(5);
    simulateLeakyBucket(duration);
    return(0);
}

