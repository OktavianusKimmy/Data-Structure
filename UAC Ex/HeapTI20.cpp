#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100
struct Heap{
	char TaskName[100];
	int UrgencyScore;
};

int size = 0;
Heap *arr[MAX];

int parent(int i){
	return (i-1)/2;
}

void swap(Heap *a, Heap *b){
	Heap t = *a;
	*a = *b;
	*b = t;
}

void insert(Heap *newData){
	if(size >= MAX){
		printf("FULL\n");
		return;
	}
	
	int i = size;
	arr[i] = newData;
	size++;
	
	while(i != 0 && arr[parent(i)]->UrgencyScore > arr[i]->UrgencyScore){
		swap(arr[parent(i)], arr[i]);
		i = parent(i);
	}
}

int left(int i){
	return (i*2)+1;
}

int right(int i){
	return (i*2)+2;
}

void popHeap(){
	if(size == 0){
		puts("No jobs pending.");
		return;
	}
	
	printf("%s\n", arr[0]->TaskName);
	arr[0] = arr[--size];
	
	int i = 0;
	while(left(i) <= size){
		int temp = left(i);
		if(right(i) <= size && arr[right(i)]->UrgencyScore < arr[left(i)]->UrgencyScore){
			temp = right(i);
		}
		if(arr[i]->UrgencyScore > arr[temp]->UrgencyScore){
			swap(arr[i], arr[temp]);
		}
		i = temp;
	}
	
}

int main(){
	int loop;
	scanf("%d", &loop); getchar();
	for(int i = 0; i<loop; i++){
		char process[10];
		scanf("%s", process); getchar();
		if(strcmp(process, "ADD") == 0){
			char TaskName[100];
			int UrgencyScore;
			scanf("%s %d", TaskName, &UrgencyScore); getchar();
			Heap *newData = (Heap*)malloc(sizeof(Heap));
			strcpy(newData->TaskName, TaskName);
			newData->UrgencyScore = UrgencyScore;
			insert(newData);
		}
		else if(strcmp(process, "PROCESS") == 0){
			popHeap();
		}
		
	}
}
