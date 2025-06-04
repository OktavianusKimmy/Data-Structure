#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node{
	int id;
	char name[100];
	int year;
	int month;
	int date;
	int height;
	Node *left;
	Node *right;
};

Node* insert(Node *root, Node *newNode){
	if(root == NULL) return newNode;
	else if(root->year < newNode->year && root->month < newNode->month && root->date < newNode->date)
}

int main(){
	Node *root = NULL;
	int inp;
	scanf("%d", &inp); getchar();
	for(int i = 0;  i<inp; i++){
		int id;
		char name[100];
			int year;
		int month;
		int date;
		scanf("%d;%[^;];%d-%d-%d", &id, name, &year, &month, &date); getchar();
		Node *newNode = (Node*)malloc(sizof(Node));
		newNode->id = id;
		strcpy(newNode->name, name);
		newNode->year = year;
		newNode->month = month;
		newNode->date = date;
		root = insert(root, newNode);
	}
	
	int del;
	scanf("%d", &del); getchar();
	for(int i = 0; i<del; i++){
		
	}
}
