#include <stdio.h>
#include <unistd.h>
#include<sys/wait.h>

int main(int argc, char *argv[]) {
    if(argc<2){
        printf("no args supplied");
    }else{
        int pid=fork();
        int stat;
        if(pid==0){
            argv=argv+1;//dont pass the program name to itself
            _exit(execvp(argv[0],(argv)));
        }else{
            wait(&stat);
            if(WIFEXITED(stat)){
                fprintf(stderr,"%d",WEXITSTATUS(stat));
            }
        }
    }
    return 0;
}
