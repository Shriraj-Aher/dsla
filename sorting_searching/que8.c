// Arrange the list of employees as per the average of their height and
// weight by using appropriate sorting method.


#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    char name[50];
    float height;
    float weight;
    float avg; // (height + weight) / 2
} Employee;

void swap(Employee *a, Employee *b) {
    Employee temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function for descending Quick Sort
int partition(Employee emp[], int low, int high) {
    float pivot = emp[low].avg;
    int start = low;
    int end = high;

    while (start < end) {
        while (emp[start].avg >= pivot && start < high) {
            start++;
        }
        while (emp[end].avg < pivot) {
            end--;
        }
        if (start < end) {
            swap(&emp[start], &emp[end]);
        }
    }

    swap(&emp[low], &emp[end]);
    return end;
}

void quickSort(Employee emp[], int low, int high) {
    if (low < high) {
        int pi = partition(emp, low, high);
        quickSort(emp, low, pi - 1);
        quickSort(emp, pi + 1, high);
    }
}

int main() {
    Employee emp[MAX];
    int n;

    printf("Enter number of employees: ");
    scanf("%d", &n);

    // Input employee details
    for (int i = 0; i < n; i++) {
        printf("\nEnter name of employee %d: ", i + 1);
        scanf("%s", emp[i].name);
        printf("Enter height (in cm) of %s: ", emp[i].name);
        scanf("%f", &emp[i].height);
        printf("Enter weight (in kg) of %s: ", emp[i].name);
        scanf("%f", &emp[i].weight);

        emp[i].avg = (emp[i].height + emp[i].weight) / 2;
    }

    // Sort based on average (descending)
    quickSort(emp, 0, n - 1);

    // Display sorted list
    printf("\n--- Employees Sorted by Average of Height and Weight ---\n");
    for (int i = 0; i < n; i++) {
        printf("Name: %s\tHeight: %.2f cm\tWeight: %.2f kg\tAverage: %.2f\n",
               emp[i].name, emp[i].height, emp[i].weight, emp[i].avg);
    }

    return 0;
}
