#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>

int pipeOne[2];
int pipeTwo[2];

volatile sig_atomic_t got_usr1;
void sigusr1_handler(int sig)
{
    printf("Pong quitting");
    exit(0);
}
void Ping(){
    close(pipeOne[0]);
    close(pipeTwo[1]);
    int ball=0;
    while(1){
        printf("ping: {%d}\n",ball);
        ball++;
        write(pipeOne[1], &ball, sizeof(ball));
        read(pipeTwo[0], &ball, sizeof(ball));
        if(ball>=100){
            close(pipeOne[1]);
            close(pipeTwo[0]);
            break;
        }
    }
}
void Pong(){
    close(pipeOne[1]);
    close(pipeTwo[0]);
    while(1){
        int ball;
        read(pipeOne[0], &ball, sizeof(ball));
        printf("pong-{%d}\n",ball);
        ball++;
        write(pipeTwo[1], &ball, sizeof(ball));
    }
}

int main(){
    struct sigaction sa;
    got_usr1 = 0;
    sa.sa_handler = sigusr1_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);

    pid_t pidOne;
    pid_t pidTwo;

    if (pipe(pipeOne))
    {
        perror("pipe one failed");
        exit(1);
    }
    if (pipe(pipeTwo))
    {
        perror("pipe two failed");
        exit(1);
    }
    pidOne=fork();
    if(pidOne==-1){
        perror("fork one failed");
        exit(EXIT_FAILURE);
    }
    if(pidOne==0) {
        Ping();
    }else {
        pidTwo=fork();
        if(pidTwo==-1){
            perror("fork two failed");
            exit(EXIT_FAILURE);
        }
        if(pidTwo==0){
            Pong();
            close(pipeOne[0]);
            close(pipeTwo[1]);
        }else{
            wait(NULL);
            kill(pidTwo, SIGUSR1);
        }
    }
}