// WAP to implement Bubble sort and Quick Sort on 1D array of Student
// structure (contains student_name, student_roll_no, total_marks), with
// key as student_roll_no. And count the number of swap performed.

#include<stdio.h>
#include<string.h>
int swap_count;
typedef struct student{
    char st_name[20];
    int st_roll;
    float st_marks;
}student;

void swap(student *a, student *b){
    student temp;
    temp = *a;
    *a = *b;
    *b = temp;
    swap_count++;
}

void print(student s[], int n){
    printf("student details in sorted order :\n");
        printf("Name\troll no.\tmarks\n");
    for(int i=0; i<n; i++){
        printf("%s\t%d\t%f\n", s[i].st_name, s[i].st_roll, s[i].st_marks);
    }
    printf("no. of swaps : %d", swap_count);
}

void bubble_sort(int n, student s[]){
    for(int i=0; i<n-1; i++){
        for(int j=0; j<n-1-i; j++){
            if(s[j].st_roll > s[j+1].st_roll)
            swap(&s[j], &s[j+1]);
        }
    }
}

int partition(student s[], int low, int high){
    int pivot = s[low].st_roll;
    int start = low;
    int end = high;
    while(start < end){
        while(s[start].st_roll <= pivot){
            start++;
        }
        while(s[end].st_roll > pivot){
            end--;
        }
        if(start < end){
            swap(&s[start], &s[end]);
        }
    }
    swap(&s[low], &s[end]);
    return end;
}

void quick_sort(student s[], int low, int high){
    if(low < high){
        int loc = partition(s, low, high);
        quick_sort(s, low, loc-1);
        quick_sort(s, loc+1, high);
    }
}

int main(){
    int n;
    printf("enter the number of students: ");
    scanf("%d", &n);

    student s[n];

    printf("enter the student details: \n");
    for(int i=0; i<n; i++){
        printf("enter name of student %d: ", i+1);
        scanf("%s", s[i].st_name);
        printf("enter the roll no of student %d: ", i+1);
        scanf("%d", &s[i].st_roll);
        printf("enter the marks of the student %d: ", i+1);
        scanf("%f", &s[i].st_marks);
    }

    int choice;
    printf("enter your choice : \n");
    printf("1. Bubble sort \n");
    printf("2. Quick sort \n");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        bubble_sort(n, s);
        print(s, n);
        break;
    
    case 2:
        quick_sort(s, 0, n-1);
        print(s, n);
        break;

    default:
    break;
    }
    
    return 0;
}