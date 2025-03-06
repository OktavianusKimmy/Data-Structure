#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Data{
    char address[50];
    char type[10];
    char id[10];
    Data *next;
}*head;

void push(char address[], char type[], char id[]){
    Data *newData = (Data*)malloc(sizeof(Data));
    strcpy(newData->address, address);
    strcpy(newData->type, type);
    strcpy(newData->id, id);
    newData->next = NULL;

    if(!head){
        head = newData;
    }
    else if(strcmp(type, "Instant") == 0){
        Data *temp = head;
        while(!(strcmp(temp->next->type, "Standard") == 0 || strcmp(temp->next->type, "Economy") == 0)){
            temp = temp->next;
        }
        newData->next = temp->next;
        temp->next = newData;
    }
    else if(strcmp(type, "Standard") == 0){
        Data *temp = head;
        while(strcmp(temp->next->type, "Economy") != 0){
            temp = temp->next;
        }
        newData->next = temp->next;
        temp->next = newData;
    }
    else{
        Data *temp = head;
        while(temp->next){
            temp = temp->next;
        }
        temp->next = newData;
    }
}

void pop(){
    if(!head){
        puts("No data");
        return;
    }
    printf("%s (%s) successfully sent to %s\n", head->id, head->type, head->address);
    Data *temp = head;
    head = head->next;
    free(temp);
}

void insert();
void send();
void view();
void exit();

int main(){
    int choice = -1;
    do{
        do{
            puts("Copi Xpress");
            puts("1. Insert new package");
            puts("2. Send a package");
            puts("3. View all package");
            puts("4. Exit");
            printf(">> ");
            scanf("%d", &choice); getchar();
    
            switch (choice){
                case 1:
                    insert();
                    break;
                case 2:
                    send();
                    break;
                case 3:
                    view();
                    break;
                case 4:
                	exit();
                    return 0;
            }
        } while(choice < 1 || choice > 4);
    } while(1);
}

int checkAddress(char *address){
    if(address[0] != 'J' || address[1] != 'l' || address[2] != '.'  || strlen(address) > 23 || strlen(address) < 8){
        return 0;
    }
    else{
        return 1;
    }
}

void insert(){
    char address[50];
    char type[10];
    char id[10];
    do{
        printf("Address (must start with \"Jl.\", 5-20 characters [inclusive]): ");
        scanf("%[^\n]", address); getchar();
    } while(checkAddress(address) == 0);

    do{
        printf("Package Type (Economy/Standard/Instant [case sensitive]): ");
        scanf("%[^\n]", type); getchar();
    } while(!(strcmp(type, "Economy") == 0 || strcmp(type, "Standard") == 0 || strcmp(type, "Instant") == 0));

    strcpy(id, "CPX");
    srand(time(NULL));
    for(int i = 0; i<3; i++){
        int random = rand() % 10;
        if(random%2 == 0){
            id[i+3] = rand() % 26 + 'A';
        }
        else{
            id[i+3] = rand() % 10 + '0';
        }
    }
    id[6] = '\0';
    push(address, type, id);
    puts("Package Inserted!");
}

void send(){
    pop();
}

void view(){
    Data *temp = head;
    while(temp){
        printf("%s - %s - %s\n", temp->id, temp->type, temp->address);
        temp = temp->next;
    }
}

void exit(){
	if(!head){
        puts("Exit Program");
        return;
    }
    Data *temp = head;
    while(temp){
	    printf("%s (%s) successfully sent to %s\n", head->id, head->type, head->address);
	    head = head->next;
    	free(temp);
    	temp = temp->next;
	}
	puts("Exit Program");
	return;
}
