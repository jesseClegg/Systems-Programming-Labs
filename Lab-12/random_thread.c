#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

int randomNumbers[1000000];
int threadSum;
int realSum;


void* firstHalf(){
    for(int i=0; i<=499999; i++){
        threadSum+=randomNumbers[i];
    }
}

void* secondHalf(){
    for(int i=500000; i<=999999; i++){
        threadSum+=randomNumbers[i];
    }
}

int main() {
    //create one million random numbers
    int current=0;
    srand(time(NULL));
    current=rand()%10;
    for(int i=0; i<999999; i++){
        current=rand()%10;
        randomNumbers[i]=current;
    }

    pthread_t thread1, thread2;

    //create 2 threads
    pthread_create(&thread1, NULL, &firstHalf, NULL);
    pthread_create(&thread2, NULL, &secondHalf, NULL);

    //wait for threads
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    //print the sum
    printf("Calculated with threads [%d]\n", threadSum);

    //sum the array itself
    for(int i=0; i<999999; i++){
        realSum+=randomNumbers[i];
    }

    //print the actual result
    printf("Without threads, result should match now [%d]\n", realSum);
    return 0;
}
