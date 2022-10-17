#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int main() {
    srand(time(NULL));
    int numberPool[100];
    for(int i=0; i<100; i++){
        numberPool[i]=rand()%100;
    }
    int sum=0;
    int temp=0;
    for(int i=0; i<100; i++){
        temp=numberPool[i];
        sum=sum+temp;
    }
    printf("sum=[%d]\n", sum);
    char sumName[99];
    char * filePrefix="numbers_";
    FILE *fileptr;
    char * fileName="numbers_";
    fileptr=fopen(fileName, "w");
    for(int i=0; i<100; i++){
        fprintf(fileptr,"%d ",numberPool[i]);
        printf(" %d", numberPool[i]);
    }
    //int fn=snprintf(sumName, 9,"%s",filePrefix);
    //itoa (sum,sumName,10); //10 for decimal/base 10
    //printf("sumname=%s\n", sumName);
    //strcat(filePrefix,sumName);
    //printf("%s\n", filePrefix);
    //then write the numbers to a new file
    //filename should be numbers_XXXX.txt
    //XXXX is the sum of the numbers
    return 0;
}
