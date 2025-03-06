#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node{
    char name[20];
    char type[20];
    Node *next;
    Node *prev;
}*head, *tail;

void regis();
void remove();
void call();

void push(char name[], char type[], int prior){
    Node *newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    strcpy(newNode->type, type);
    newNode->next = NULL;
    newNode->prev = NULL;

    if(prior == 1){
        if(!head){
            head = tail = newNode;
        }
        else{
            Node *temp = head;
            while(temp->next){
                if(strcmp(temp->next->type, "REGULER") == 0){
                    break;
                }
                else{
                    temp = temp->next;
                }
            }
            newNode->next = temp->next;
            temp->next = newNode;
            newNode->next->prev = newNode;
            newNode->prev = temp;
        }
    }
    else{
        if(!head){
            head = tail = newNode;
        }
        else{
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
}

int main(){
    do{
        printf("Istana Boneka\n");
        printf("REGISTER / REMOVE CALL\n");
        char input[10];
        do{
            scanf("%s", input); getchar();
            if(strcmp(input, "REGISTER") == 0){
                regis();
            }
            else if(strcmp(input, "REMOVE") == 0){
                remove();
            }
            else if(strcmp(input, "CALL") == 0){
                call();
            }
            else{
                puts("Wrong Input");
            }
        } while(!(strcmp(input, "REGISTER") == 0 || strcmp(input, "REMOVE") == 0 || strcmp(input, "CALL") == 0));
    } while(1);
}

void regis(){
    int jumlah;
    scanf("%d", &jumlah); getchar();
    for(int i = 0; i<jumlah; i++){
        char name[20];
        char type[20];
        int prior = 0;
        do{
            scanf("%s %[^\n]", name, type); getchar();
            if(strcmp(type, "REGULER") == 0){
                prior = 2;
                push(name, type, prior);
            }
            else if(strcmp(type, "FAST_TRACK") == 0){
                prior = 1;
                push(name, type, prior);
            }
            else{
                prior = 0;
                puts("Wrong Input");
            }
        } while(prior == 0);
    }
    Node *temp = head;
    int i = 1;
    printf("No Name\tTicket\n");
    while(temp){
        printf("%d %s\t%s\n", i, temp->name, temp->type);
        i++;
        temp = temp->next;
    }
}

void remove(){
    int jumlah;
    scanf("%d", &jumlah); getchar();
    for(int i = 0; i<jumlah; i++){
        char name[20];
        int flag = 0;
        do{
            scanf("%[^\n]", name); getchar();
            Node *temp = head;
            while(temp){
                if(strcmp(temp->name, name) == 0){
                    Node *temp2 = temp->prev;
                    temp2->next = temp->next;
                    temp->next->prev = temp2;
                    printf("%s removed!", temp->name);
                    free(temp);
                    flag = 1;
                    break;
                }
                temp = temp->next;
            }
            if(flag == 0 ){
                puts("No exist name! input again");
            }
        } while(flag == 0);
    }

    Node *temp = head;
    int i = 1;
    printf("No Name\tTicket\n");
    while(temp){
        printf("%d %s\t%s\n", i, temp->name, temp->type);
        i++;
        temp = temp->next;
    }
}

void call(){
    Node *temp = head;
    for(int i = 0; i<4; i++){
        if(!head) break;
        printf("%s ", head->name);
        head = head->next;
        free(temp);
    }
    puts("got into the boat.");
    
    int count = 0;
    Node *temp2 = head;
    while(temp2 != NULL){
        count++;
        temp2 = temp2->next;
    }
    printf("%d queues remaining.\n", count);
}