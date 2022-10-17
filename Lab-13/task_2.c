#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

void uhoh(const char *msg){
    perror(msg);
    exit(EXIT_FAILURE);
}

int main() {
    int fd1;
    struct stat sb;
    size_t length;
    fd1 = open("data", O_RDONLY, 0777);
    if(fd1 == -1){
        uhoh("problem with file open");
    }
    if(fstat(fd1, &sb)==-1){
        uhoh("fstat problem");
    }
    length = sb.st_size;
    char *addr=mmap(NULL, length, PROT_READ, MAP_SHARED, fd1, 0);
    if(addr==MAP_FAILED){
        uhoh("mmap failed");
    }
    int sharedFD = shm_open("/sharedSpace", O_RDWR|O_CREAT, 0777);
    if(sharedFD==-1){
        uhoh("sharedFD messed up");
    }
    int trunco = ftruncate(sharedFD, length);
    void *realMapping = mmap(NULL, length, PROT_READ|PROT_WRITE, MAP_SHARED, sharedFD, 0);
    if(realMapping==MAP_FAILED){
        uhoh("realMapping error");
    }
    void * copied = memcpy(realMapping, addr, length);
    int uMapFile = munmap(addr, length);
    if(uMapFile==0){
        printf("successful unmapping of file area\n");
    }
    int uMapReal = munmap(realMapping, length);
    if(uMapReal==0){
        printf("successful unmapping of shared area\n");
    }
    int didClose = close(fd1);
    if(didClose==0){
        printf("successful closing of file\n");
    }
    return 0;
}
