// Write a program, using trees, to assign the roll nos. to the students of
// your class as per their previous years result. i.e topper will be roll no. 1.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student {
    char name[20];
    int marks;
    struct student *left, *right;
} student;

// Insert into BST based on marks
student* insert(student *root, int marks, char name[]) {
    
        student* newNode = (student*)malloc(sizeof(student));
        strcpy(newNode->name, name);
        newNode->marks = marks;
        newNode->left = newNode->right = NULL;
        
    if(root == NULL){
        return newNode;
    }

   struct student* current = root;
    struct student* parent = NULL;

    while (current != NULL) {
        parent = current;
        if (marks < current->marks)
            current = current->left;
        else
            current = current->right;
    }

    if (marks < parent->marks)
        parent->left = newNode;
    else
        parent->right = newNode;

    return root;
}

// Reverse Inorder to assign roll numbers (highest marks first)
void assignRollNumbers(student *root, int *rollNo) {
    if (!root) return;

    assignRollNumbers(root->right, rollNo); // Higher marks first
    printf("Roll No: %d | Name: %s | Marks: %d\n", (*rollNo)++, root->name, root->marks);
    assignRollNumbers(root->left, rollNo);
}

int main() {
    int n;
    printf("Enter the number of students: ");
    scanf("%d", &n);

    student *root = NULL;
    for (int i = 0; i < n; i++) {
        char name[20];
        int marks;
        printf("Enter name of student %d: ", i + 1);
        scanf("%s", name);
        printf("Enter marks of student %d: ", i + 1);
        scanf("%d", &marks);
        root = insert(root, marks, name);
    }

    int roll = 1;
    printf("\nAssigned Roll Numbers:\n");
    assignRollNumbers(root, &roll);

    return 0;
}
