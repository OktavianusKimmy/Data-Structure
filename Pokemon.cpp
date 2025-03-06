#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int count = 100;
struct Node{
    int ID;
    char Name[25];
    int Price;
    struct Node *next;
} *head, *tail, *current;

void printList(struct Node* head) {
    while (head != NULL) {
        printf("ID  : %d\nName : %s\nPrice: %d\n", head->ID, head->Name, head->Price);
        head = head->next;
        printf("---------------------------------\n");
    }
}

void pushmid(char Name[]){
    srand(time(NULL));
    current = (struct Node*)malloc(sizeof(struct Node)); // Declare malloc Current
    strcpy(current->Name, Name);
    current->ID = count;
    count++;
    current->Price = rand() % 9000 + 1000;
    current->next = NULL; // Current->next = NULL
    if(!head){
        head = tail = current;
    } else if(strcmp(Name, head->Name) < 0){ 
        current->next = head;
        head = current;
    } else if(strcmp(Name, tail->Name) > 0){
        tail->next = current;
        tail = current;
    } else {
        Node *temp = head;
        while(strcmp(temp->next->Name, Name) < 0){
            temp = temp->next;
        }
        current->next = temp->next;
        temp->next = current;
    }
}

void popHeadMid(char target[]){
    if(head == NULL){
        return;
    }
    if (strcmp(head->Name, target) == 0){
        struct Node *temp = head;
        head = head->next;
        temp -> next = NULL;
        free(temp);
    } else {
        struct Node *temp1 = head;
        struct Node *temp2 = head->next;
        while(strcmp(temp2->Name, target) != 0){
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        temp1->next = temp2->next;
        temp2->next = NULL;
        free(temp2);
    }    
}

void BuyCard(){
    char temp[25];
    printf("Input Card Name you Want: ");
    scanf("%[^\n]", temp);getchar();
    pushmid(temp);
    printf("%s has been inputted\n", temp);
    printf("---------------------------------\n");
}

void ShowCard(){
    printList(head);
    printf("---------------------------------\n");
}

void DeleteCard(){
    char temp[25];
    printf("Input Card Name you Want to Delete: ");
    scanf("%[^\n]", temp);getchar();
    popHeadMid(temp);
    printf("%s has been deleted\n", temp);
    printf("---------------------------------\n");
}

void ChangeCard(){
    BuyCard();
    DeleteCard();
    ShowCard();
}

int main(){
    srand(time(NULL));
    int choice;
    char Nama[25];
    strcpy(Nama, "Vulpix");
    pushmid(Nama);
    srand(time(NULL));

    strcpy(Nama, "Diglett");
    pushmid(Nama);
    srand(time(NULL));

    strcpy(Nama, "Zubat");
    pushmid(Nama);
    srand(time(NULL));

    strcpy(Nama, "Nidoran");
    pushmid(Nama);
    
    do{
        printf("Card Changer\n");
        printf("1. Buy Card\n");
        printf("2. Show Card\n");
        printf("3. Change Card\n");
        printf("4. Delete Card\n");
        printf("5. Exit\n");
        do{
            printf("Choice : ");
            scanf("%d", &choice);getchar();
            if (choice < 1 || choice > 6){
                printf("Invalid Input\n");
            }
        } while (choice < 1 || choice > 6);

        switch (choice){
        case 1:
            BuyCard();
            printf("Enter to Continue\n"); getchar();
            break;
        case 2:
            ShowCard();
            printf("Enter to Continue\n"); getchar();
            break;
        case 3:
            ChangeCard();
            printf("Enter to Continue\n"); getchar();
            break;
        case 4:
            DeleteCard();
            printf("Enter to Continue\n"); getchar();
            break;
        }
        system("cls");
    } while (choice != 5);
	return 0;
}
