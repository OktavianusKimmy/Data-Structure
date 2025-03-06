#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#define SIZE 50 
 
struct Data{ 
 char coin[5]; 
 double price; 
 Data *next; 
} *arr[SIZE]; 
 
int midSquare(char coin[]){ 
	int len = strlen(coin);
	int key = 0;
	for(int i = 0; i<len; i++){
		key += coin[i];
	}
	key *= key;
	char keyString[10];
	sprintf(keyString, "%d", key);
	int a = strlen(keyString);
	if(a % 2 == 0){
		char balikin[2];
		balikin[0] = keyString[(a/2)-1];
		balikin[1] = keyString[a/2];
		int balikinInt = (balikin[0] - '0') * 10;
		balikinInt += balikin[1] - '0';
		printf("%d\n", balikinInt);
		return balikinInt % SIZE;
	}
	else{
		char balikin[2];
		balikin[0] = keyString[(a/2)];
		int balikinInt = balikin[0] - '0';
		printf("%d\n", balikinInt);
		return balikinInt % SIZE;
	}
} 
 
void insert(char coin[], double price){ 
	Data *data = (Data*)malloc(sizeof(Data)); 
	data->price = price; 
	strcpy(data->coin, coin); 
	data->next = NULL; 
	puts("..");
	int index = midSquare(coin); 
	//Insert with chaining collision handling
	if(arr[index] == NULL){
		arr[index] = data;
	}
	else{
		Data *temp = arr[index];
		while(temp->next){
			temp = temp->next;
		}
		temp->next = data;
	}
} 
 
int main(){ 
 insert("BTC", 97000.00); 
 insert("ETH", 2700.00); 
 insert("SOL", 172.59); 
 insert("XRP", 2.57); 
  
 return 0; 
} 
