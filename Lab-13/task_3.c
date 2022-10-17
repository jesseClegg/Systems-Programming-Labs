#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>

int main(){
    int filePtr = open("data_copied", O_CREAT|O_RDWR, 0777);
    if(filePtr<0){
        perror("opening the file problem\n");
    }
    int trunk = ftruncate(filePtr, 10000);
    void *newFileMapping = mmap(NULL, 10000, PROT_READ | PROT_WRITE, MAP_SHARED, filePtr, 0);
    if(newFileMapping == MAP_FAILED){
        perror("mmap oopsie newFileMapping\n");
    }
    int sharedFD = shm_open("/sharedSpace", O_RDWR, 0777);
    if(sharedFD==-1){
        printf("oopsie at shm_open for sharedFD\n");
    }
    void *sharedSpaceMapping = mmap(NULL, 10000, PROT_READ | PROT_WRITE, MAP_SHARED, sharedFD,0);
    memcpy(newFileMapping, sharedSpaceMapping, 10000);
    int uMapShared = munmap(sharedSpaceMapping, 10000);
    if(uMapShared==0){
        printf("shared space unmapped successfully\n");
    }
    int uMapNewFile = munmap(newFileMapping, 10000);
    if(uMapNewFile==0){
        printf("new file space unmapped successfully\n");
    }
    int didClose = close(filePtr);
    if(didClose==0){
        printf("file descriptor closed successfully\n");
    }
    int unLink = shm_unlink("/sharedSpace");
    if(unLink==0){
        printf("shm_unlinking successful\n");
    }
    return 0;
}
