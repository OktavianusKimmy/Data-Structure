#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Data{
	char name[105];
	int age;
	int priority;
	struct Data* next;
};

Data *h = NULL;

Data *createData(char name[], int age, char status[]){
	Data *c = (struct Data*)malloc(sizeof(struct Data));
	strcpy(c->name, name);
	c->age = age;
	
	if(strcmp(status, "High") == 0){
		c->priority = 1;
	}else if(strcmp(status, "Mid") == 0){
		c->priority = 2;
	}else if(strcmp(status, "Low") == 0){
		c->priority = 3;
	}
	c->next = NULL;
	return c;
}

void enqueue(char name[], int age, char status[]){
	Data *c = createData(name, age, status);
	// kalau antrian kosong atau ada prioritas yg lbh tinggi
	if(h == NULL || c->priority < h->priority){
		c->next = h;
		h = c;
	}else{
		Data *temp = h;
		// geser posisi temp sampe sesuai utk enqueue pasien brdasarkan prioritas
		while(temp->next && temp->next->priority <= c->priority){
			temp = temp->next;
		}
		c->next = temp->next;
		temp->next = c;
	}
}

void dequeue(){
	if(h == NULL){
		printf("There is no patient to process.\n");
		return;
	}
	Data* del = h;
	h = h->next;
	free(del);
}

void view(){
	if(h == NULL){
		printf("There is no patient to process.\n");
		return;
	}
	Data *temp = h;
	while(temp != NULL){
		printf("Nama: %s, Umur: %d, Status: %d\n",
		temp->name, temp->age, temp->priority);
		temp = temp->next;
	}
}

int main(){
	enqueue("Rizki", 33, "Low");
	enqueue("Richard", 26, "Low");
	enqueue("Andi", 16, "High");
	enqueue("Nur", 74, "Mid");
	enqueue("Coki", 66, "Low");
	
	printf("Linked list after entering data:\n");
	view();
	
	printf("\n");
	printf("After process:\n");
	dequeue();
	dequeue();
	dequeue();

	view();
	
	return 0;
}
