#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node {
    int data;
    struct node *next;
};

int main() {
    int randomNumber;
    srand(time(NULL));
    struct node * head=(malloc(sizeof(struct node)));
    struct node * current=(malloc(sizeof(struct node)));
    head->next=current;
    while(1){
         randomNumber=((rand()) % 51);
            if(randomNumber == 49){
                break;
            }
        current->data=randomNumber;
        struct node * temp=(malloc(sizeof(struct node)));
        current->next=temp;
        current=temp;
        }
    current=head->next;//remember to set current back to head
    free(head);//head no longer needed, free it now
    struct node * temp2;//just so we don't lose nodes, doesn't need its own memory
    while(current->next!=NULL){
        printf("%d, ", current->data);//action takes place here BEFORE reassignment
        temp2=current->next;
        free(current);
        current=temp2;
    }
    free(current);//remember to go back and free current, not done in loop
    exit(0);//exits when done
}

