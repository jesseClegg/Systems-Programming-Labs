#include <stdio.h>

int main(){
    FILE * fileptr;
    fileptr= fopen("numbers_","r");
    int temp=0;
    int sum=0;

    //for(int i=0; i<100; i++){
      while(!feof(fileptr)){
        temp=fscanf(fileptr,"d");
        printf("%d", temp);
        sum=sum+temp;
    }





    return 0;
}