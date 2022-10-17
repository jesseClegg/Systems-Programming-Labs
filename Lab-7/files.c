#include <stdio.h>

int main() {
    char fileName[]="input.txt";
    FILE* filePtr;
    filePtr= fopen(fileName, "r");
    char currentLine[99];
    while(!feof(filePtr)) {
        fscanf(filePtr,"%s", currentLine);
        printf("%s\n", currentLine);
    }
    fclose(filePtr);
    return 0;
}