#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Student{
	int id;
	int exam_pass;
	int have_c_grade;
	int international_achiev;
	int value;
	int height;
	Student *left;
	Student *right;
};

/*

func, id, exam_pass, have_c_grade, international_achiev

11
i 1 1 0 10
i 2 1 0 6
i 3 1 1 8
i 4 1 1 5
i 5 0 0 5
i 6 1 0 7
i 7 1 0 9
d 2
d 1
d 3
d 4
*/

Student* create(int id, int exam_pass, int have_c_grade, int international_achiev){
	Student *newStudent = (Student*)malloc(sizeof(Student));
	newStudent->id = id;
	newStudent->exam_pass = exam_pass;
	newStudent->have_c_grade = have_c_grade;
	newStudent->international_achiev = international_achiev;
	if(exam_pass == 0 && have_c_grade == 1) newStudent->value = 0;
	else if(exam_pass == 0 && have_c_grade == 0) newStudent->value = 1;
	else if(exam_pass == 1 && have_c_grade == 1) newStudent->value = 2;
	else if(exam_pass == 1 && have_c_grade == 0) newStudent->value = 3;
	newStudent->height = 1;
	newStudent->left = NULL;
	newStudent->right = NULL;
	return newStudent;
}

int height (Student *root){
	if(root == NULL) return 0;
	return root->height;
}

int max(int a, int b){
	return a > b ? a : b;
}

int getBalanceFactor(Student *root){
	if(root == NULL) return 0;
	return height(root->left) - height(root->right);
}

Student* leftRotate(Student *x){
	Student *y = x->right;
	Student *z = y->left;
	
	y->left = x;
	x->right = z;
	
	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;
	
	return y;
}

Student* rightRotate(Student *x){
	Student *y = x->left;
	Student *z = y->right;
	
	y->right = x;
	x->left = z;
	
	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;
	
	return y;
}

Student* insert(Student *root, Student *newStudent){
	if(root == NULL) return newStudent;
	else if(root->value > newStudent->value) root->left = insert(root->left, newStudent);
	else if(root->value < newStudent->value) root->right = insert(root->right, newStudent);
	else if(root->value == newStudent->value){
		if(root->international_achiev > newStudent->international_achiev) root->left = insert(root->left, newStudent);
		else root->right = insert(root->right, newStudent);
	}
	else return root;
	
	root->height = max(height(root->left), height(root->right)) + 1;
	int balance = getBalanceFactor(root);
	
	if(balance > 1){
		if(getBalanceFactor(root->left) >= 0) return rightRotate(root);
		else{
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}
	}
	else if(balance < -1){
		if(getBalanceFactor(root->right) <= 0) return leftRotate(root);
		else{
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}
	}
	return root;
}

Student* del(Student *root, int id);

Student *deleteAVL(Student *root, int id){
	if(root->left == NULL && root->right == NULL){
		// tidka punya anak
		free(root);
		return NULL;
	}
	else if(root->left == NULL || root->right == NULL){
		Student *temp = root->left ? root->left : root->right;
		free(root);
		return temp;
	}
	else{
		Student *temp = root->left;
		while(temp->right){
			temp = temp->right;
		}
		root->id = temp->id;
		root->value = temp->value;
		root->exam_pass = temp->exam_pass;
		root->have_c_grade = temp->have_c_grade;
		root->international_achiev = temp->international_achiev;
		root->left = del(root->left, temp->id);
	}
	
	root->height = max(height(root->left), height(root->right)) + 1;
	int balance = getBalanceFactor(root);
	
	if(balance > 1){
		if(getBalanceFactor(root->left) >= 0) return rightRotate(root);
		else{
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}
	}
	else if(balance < -1){
		if(getBalanceFactor(root->right) <= 0) return leftRotate(root);
		else{
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}
	}
	return root;
}


Student* del(Student *root, int id){
	if(root != NULL){
		if(root->id == id){
			root = deleteAVL(root, id);
			return root;
		}
		root->left = del(root->left, id);
		root->right = del(root->right, id);
		return root;
	}
	return NULL;
}

void updateTop3(Student *node, Student *top3[3]) {
    for (int i = 0; i < 3; i++) {
        if (top3[i] == NULL) {
            top3[i] = node;
            return;
        }

        if (node->value > top3[i]->value ||
           (node->value == top3[i]->value && node->international_achiev > top3[i]->international_achiev)) {
            for (int j = 2; j > i; j--) {
                top3[j] = top3[j - 1];
            }
            top3[i] = node;
            return;
        }
    }
}

void findTop3(Student *root, Student *top3[3]) {
    if (root == NULL) return;

    updateTop3(root, top3);
    findTop3(root->left, top3);
    findTop3(root->right, top3);
}

void in(Student *root){
	if(root != NULL){
		printf("%d\n", root->id);
		in(root->left);
		in(root->right);
	}
}

int main(){
	Student *root = NULL;
	int loop;
	scanf("%d", &loop);getchar();
	for(int i = 0; i<loop; i++){
		char func;
		scanf("%c", &func);
		if(func == 'i'){
			int id, exam_pass, have_c_grade, international_achiev;
			scanf(" %d %d %d %d", &id, &exam_pass, &have_c_grade, &international_achiev); getchar();
			Student *newNode = create(id, exam_pass, have_c_grade, international_achiev);
			root = insert(root, newNode);
		}
		else if(func == 'd'){
			int id;
			scanf("%d", &id); getchar();
			root = del(root, id);
		}
	}
	
//	in(root);
	
	Student *top3[3] = {NULL, NULL, NULL};
	findTop3(root, top3);
	
	for (int i = 0; i < 3; i++) {
	    printf("%d ", top3[i]->id);
	}
}
