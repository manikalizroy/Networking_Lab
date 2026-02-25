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
