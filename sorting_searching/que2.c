// WAP to implement Insertion sort and Merge Sort on 1D array of
// Student structure (contains student_name, student_roll_no, total_marks),
// with key as student_roll_no. And count the number of swap performed.

#include<stdio.h>
#include<string.h>

int swapcount = 0;
typedef struct student{
    char name[30];
    int roll;
    float marks;
}student;

void swap(student *a, student *b){
    student temp;
    temp = *a;
    *a = *b;
    *b = temp;
    swapcount++;
}

void print(int n, student s[]){
    printf("sorted details of student: \n");
    printf("roll no\tnamr\tmarks\n");
    for(int i=0; i<n; i++){
        printf("%d\t%s\t%f", s[i].roll, s[i].name, s[i].marks);
        printf("\n");
    }
}

void insertion_sort(int n, student s[]){

    for(int i=1; i<n; i++){
        student temp = s[i];
        int j = i-1;
        while( j >= 0 && s[j].roll > temp.roll){
            s[j+1] = s[j];
            j--;
            swapcount++;
        }
        s[j+1] = temp;
    }

}

void merge(student s[], int low, int mid, int high, int n){
    int i=low;
    int j= mid+1;
    int k=0;
     student a[n];
     while (i<=mid && j<=high){
        if(s[i].roll < s[j].roll){
            a[k] = s[i];
            i++;
            k++;
        }

        if(s[i].roll > s[j].roll){
            a[k] = s[j];
            j++;
            k++;
            swapcount++;
        }
     }

     while(i <= mid){
        a[k] = s[i];
        i++;
        k++;
     }

     while(j <= high){
        a[k] = s[j];
        j++;
        k++;
     }

     for(int i=low, k=0; i<=high; i++,k++){
        s[i] = a[k];
     }
     
}
void merge_sort(student s[], int low, int high, int n){
    int mid;
    if(low < high){
        mid = (low + high) / 2;
        merge_sort(s, low, mid, n);
        merge_sort(s, mid+1, high, n);
        merge(s, low, mid, high, n);
    }6
}

int main(){
    int n;
    printf("enter the number of students: ");
    scanf("%d", &n);
    student s[n];
    printf("\nenter the details of the students\n");
    for(int i=0; i<n; i++){
        printf("name of student %d: ", i+1);
        scanf("%s", s[i].name);
        printf("roll of student %d: ", i+1);
        scanf("%d", &s[i].roll);
        printf("marks of student %d: ", i+1);
        scanf("%f", &s[i].marks);
    }

    int choice;
    printf("menu\n");
    printf("1. insertion sort\n");
    printf("2. merge sort\n");
    printf("enter the choice: ");
    scanf("%d", &choice);
    printf("\n");
    if(choice == 1){
        insertion_sort(n, s);
        print(n, s);
    }
    else if (choice == 2)
    {
        merge_sort(s, 0, n-1, n);
        print(n, s);
    }
    else{
        printf("invalid input");
    }

    return 0;
    
}