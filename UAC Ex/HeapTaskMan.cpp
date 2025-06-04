#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100

// Min Heap

struct Heap{
	char TicketID[10];
	char RequesterName[100];
	int UrgencyLevel;
	int EstimatedMinutes;
};

int size = 0;
Heap *arr[MAX];

int parent(int i){
	return (i-1)/2;
}

void swap(Heap *a, Heap *b){
	Heap temp = *a;
	*a = *b;
	*b = temp;
}

void insert(Heap *newNode){
	if(size >= MAX){
		printf("Full\n");
		return;
	}
	
	int i = size;
	arr[i] = newNode;
	size++;
	
	while(i != 0 && arr[parent(i)]->UrgencyLevel > arr[i]->UrgencyLevel){
		swap(arr[parent(i)], arr[i]);
		i = parent(i);
	}
}

int left(int n){
	return (2*n) + 1;
}

int right(int n){
	return (2*n) + 2;	
}

void popHeap(){
	if(size == 0){
		puts("No pending tickets.");
		return;
	}
	printf("Ticket %s assigned to %s\n", arr[0]->TicketID, arr[0]->RequesterName);
	arr[0] = arr[--size];
	
	int n = 0;
	while(left(n) < size){
		int t = left(n);
		
		if(right(n) < size && arr[right(n)]->UrgencyLevel < arr[left(n)]->UrgencyLevel){
			t = right(n);
		}
		
		if(arr[t]->UrgencyLevel < arr[n]->UrgencyLevel){
			swap(arr[t], arr[n]);
			n = t;
		}
		else break;
	}
}

int main(){
	int loop;
	scanf("%d", &loop); getchar();
	for(int i = 0; i<loop; i++){
		char task[10];
		scanf("%s", task);
		if(strcmp(task, "ENQUEUE") == 0){
			char TicketID[10];
			char RequesterName[100];
			int UrgencyLevel;
			int EstimatedMinutes;
			scanf("%s %s %d %d", TicketID, RequesterName, &UrgencyLevel, &EstimatedMinutes); getchar();
			Heap *newNode = (Heap*)malloc(sizeof(Heap));
			strcpy(newNode->TicketID, TicketID);
			strcpy(newNode->RequesterName, RequesterName);
			newNode->UrgencyLevel = UrgencyLevel;
			newNode->EstimatedMinutes = EstimatedMinutes;
			insert(newNode);
		}
		else if(strcmp(task, "NEXT_TICKET") == 0){
			popHeap();
		}
	}
}
