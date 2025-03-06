#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node { // Node
    int valueNode; // isi dari node
    struct Node *next; // pointer ke node selanjutnya NULL jika tidak ada
}*head, *tail, *current; // head = node pertama, tail = node terakhir, current = node yang sedang diakses

// struct Node* createNode(int data) {
//     struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
//     newNode->data = data;
//     newNode->next = NULL;
//     return newNode;
// }

void printList(struct Node* head) {
    while (head != NULL) {
        printf("%d -> ", head->valueNode);
        head = head->next;
    }
    printf("NULL\n");
}

/*
Push Head:
1. Current -> Head
2. Head = Current
*/
void pushhead(int valueNode){
    current = (struct Node*)malloc(sizeof(struct Node));
    current->valueNode = valueNode;
    current->next = NULL;
    if(!head){
        head = tail = current;
    } else {
        current->next = head;
        head = current;
    }
}

/*
Push Tail:
1. Tail -> Current
2. Tail = Current 
*/
void pushtail(int valueNode){
    current = (struct Node*)malloc(sizeof(struct Node));
    current->valueNode = valueNode;
    current->next = NULL;
    if(!head){
        head = tail = current;
    } else {
        tail->next = current;
        tail = current;
    }
}

/*
Push Mid:
1. Current -> NULL = Temp -> Next
2. Temp -> Current 
*/
void pushmid(int valueNode){
    current = (struct Node*)malloc(sizeof(struct Node));
    current->valueNode = valueNode;
    current->next = NULL;
    if(!head){
        head = tail = current;
    } else if(head->valueNode > valueNode){ 
        current->next = head;
        head = current;
    } else if(tail->valueNode < valueNode){
        tail->next = current;
        tail = current;
    } else {
        struct Node *temp = head;
        while(temp->next->valueNode < valueNode){
            temp = temp->next;
        }
        current->next = temp->next;
        temp->next = current;
    }
}

/*
Pop Head:
1. Head = Head -> Next
2. Temp -> Next = Null
3. Free Temp
*/
void pophead(){
    if(head == NULL){
        return;
    }
    struct Node *temp = head;
    head = head->next;
    free(temp);
}

/*
Pop Tail:
1. if Temp -> Next = Tail 
2. Tail = Temp
3. Temp = Temp -> Next
4. Tail -> Next = NULL
5. Free Temp
*/
void poptail(){
    if(head == NULL){
        return;
    }
    struct Node *temp = head;
    while(temp->next->valueNode != tail->valueNode){
        temp = temp->next;
    }
    tail = temp;
    struct Node *current;
    current = temp->next;
    temp->next = NULL;
    free(current);
}

/*
Pop Mid:
1. Temp 1 = before search, temp 2 = search
2. temp 1 -> next = temp 2 -> next
3. temp 2 -> next = NULL
4. free temp 2
*/
//void popmid(int Target){
//    if(head == NULL){
//        return;
//    }
//    struct Node *temp1 = head;
//    struct Node *temp2 = head->next;
//    while(temp2->valueNode != Target){
//        temp1 = temp1->next;
//        temp2 = temp2->next;
//    }
//    temp1->next = temp2->next;
//    temp2->next = NULL;
//    free(temp2);
//}

void popmid(int target){
//	if(target == NULL) return;
	struct Node *temp1 = head;
	struct Node *temp2 = head->next;
	
	while(temp1->next->valueNode != target){
		temp1 = temp1->next;
	}
	temp2 = temp1->next;
	
//	while(temp2->valueNode != target->valueNode){
//		temp2 = temp2->next;
//	}
	
	struct Node *curr;
	curr = temp2;
	
	temp1->next = curr->next;
	free(temp2);
}

int main(){
    // struct Node* head = createNode(10);
    // head->next = createNode(20);
    // head->next->next = createNode(30);
    // head->next->next->next = createNode(40);
    pushmid(10);
    pushmid(30);
    pushmid(50);
    pushmid(70);
    pushmid(90);
    printList(head);
    popmid(70);
    printList(head);
	return 0;
}
