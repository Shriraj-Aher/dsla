// Using Quick sort, assign the roll nos. to the students of your class as per
// their previous years result. i.e. topper will be roll no. 1

#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    char name[50];
    float marks;
    int st_roll; // Temporary for sorting (we'll assign actual roll after sorting)
} student;

void swap(student *a, student *b) {
    student temp = *a;
    *a = *b;
    *b = temp;
}

int partition(student s[], int low, int high) {
    float pivot = s[low].marks; // Pivot on marks, not roll number
    int start = low;
    int end = high;

    while (start < end) {
        while (s[start].marks >= pivot && start < high) {
            start++;
        }
        while (s[end].marks < pivot) {
            end--;
        }
        if (start < end) {
            swap(&s[start], &s[end]);
        }
    }

    swap(&s[low], &s[end]);
    return end;
}

void quickSort(student s[], int low, int high) {
    if (low < high) {
        int pi = partition(s, low, high);
        quickSort(s, low, pi - 1);
        quickSort(s, pi + 1, high);
    }
}

int main() {
    student s[MAX];
    int n;

    printf("Enter number of students: ");
    scanf("%d", &n);

    // Input student details
    for (int i = 0; i < n; i++) {
        printf("\nEnter name of student %d: ", i + 1);
        scanf("%s", s[i].name);
        printf("Enter marks of %s: ", s[i].name);
        scanf("%f", &s[i].marks);
        s[i].st_roll = 0; // placeholder
    }

    // Sort students by marks in descending order using Quick Sort
    quickSort(s, 0, n - 1);

    // Assign roll numbers based on rank (topper gets 1)
    for (int i = 0; i < n; i++) {
        s[i].st_roll = i + 1;
    }

    // Print result
    printf("\n--- Roll Numbers Assigned Based on Marks ---\n");
    for (int i = 0; i < n; i++) {
        printf("Roll No: %d\tName: %s\tMarks: %.2f\n", s[i].st_roll, s[i].name, s[i].marks);
    }

    return 0;
}
