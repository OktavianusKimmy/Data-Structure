#include <stdio.h>
#include <stdlib.h>

struct Student{
	int age;
	int height;
}arrStudent[5];

int main(){
//	int a = 10;
//	int* ptr = &a;
//	
//	printf("memory dari ptr: %d\n", &ptr);
//	printf("value dari ptr: %d\n", ptr);
//	printf("value dari memory yang disimpan: %d\n", *ptr);
//	
//	*ptr = 20;
//	printf("nilai a sekarang: %d\n", *ptr);

	Student ppti;
	ppti.age = 20;
	ppti.height = 200;
	
//	Memory allocation example
	int* ptr = (int *)malloc(sizeof(int));
	*ptr = 20;
	printf("alamat baru: %d, value dari alamat: %d\n", ptr, *ptr);
	
	// Alokasi memori untuk struct
	Student* ptr2 = (Student*)malloc(sizeof(Student));
	
	//akses anggota dari struct pointer
	ptr2->age = 21;
	ptr2->height = 175;
	
	printf("age: %d, height: %d\n", ptr2->age, ptr2->height);
	
	free(ptr2);
	
	//akses anggota dari array of struct
	arrStudent[0].age = 12;
	arrStudent[1].age = 13;
	
}
