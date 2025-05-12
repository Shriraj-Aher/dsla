#include <stdio.h>
#include <string.h>

int swapcount = 0;

typedef struct employee {
    char name[30];
    int no;
    float salary;
} employee;

void print(int n, employee e[]) {
    printf("\nSorted employee details:\n");
    printf("Name\tNumber\tSalary\n");
    for (int i = 0; i < n; i++) {
        printf("%s\t%d\t%.2f\n", e[i].name, e[i].no, e[i].salary);
    }
    printf("Total swaps performed: %d\n", swapcount);
}

void selection_sort(int n, employee e[]) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (e[j].no < e[min].no) {
                min = j;
            }
        }
        if (min != i) {
            employee temp = e[i];
            e[i] = e[min];
            e[min] = temp;
            swapcount++;
        }
    }
}

void maxheapify(employee e[], int n, int i) {
    int largest = i;
    int left = (2 * i) + 1;
    int right = (2 * i) + 2;

    if (left < n && e[left].no > e[largest].no)
        largest = left;

    if (right < n && e[right].no > e[largest].no)
        largest = right;

    if (largest != i) {
        employee temp = e[i];
        e[i] = e[largest];
        e[largest] = temp;
        swapcount++;
        maxheapify(e, n, largest);
    }
}

void heap_sort(int n, employee e[]) {
    // Build max heap // n/2 -1 last parent id 
    for (int i = n / 2 - 1; i >= 0; i--) {
        maxheapify(e, n, i);  
    }

    // One by one extract elements
    for (int i = n - 1; i > 0; i--) {
        // Swap root with end
        employee temp = e[0];
        e[0] = e[i];
        e[i] = temp;
        swapcount++;

        // Heapify reduced heap
        maxheapify(e, i, 0);  // `i` is reduced heap size
    }
}

int main() {
    int n;
    printf("Enter the number of employees: ");
    scanf("%d", &n);

    employee e[n];
    printf("Enter the employee details:\n");
    for (int i = 0; i < n; i++) {
        printf("\nName of employee %d: ", i + 1);
        scanf("%s", e[i].name);
        printf("Emp_no of employee %d: ", i + 1);
        scanf("%d", &e[i].no);
        printf("Salary of employee %d: ", i + 1);
        scanf("%f", &e[i].salary);
    }

    int choice;
    printf("\nMenu:\n1. Selection Sort\n2. Heap Sort\nEnter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        selection_sort(n, e);
        print(n, e);
    } else if (choice == 2) {
        heap_sort(n, e);
        print(n, e);
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}
