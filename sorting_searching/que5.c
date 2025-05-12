// Write a program to arrange the data of the faculties recruited in the
// institute. There are three categories of faculties in the every deartment
// namely professor, Associate professor, and assistant professor.
// Recruitment is done as mentioned below. 1. Every professor has two
// associate professors. 2. Every Associate has two assistant professors.
// Data is given randomly. Suggest suitable sorting method and implement
#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    char name[50];
    char role[20];
    int priority;
} faculty;

int getpriority(char *role) {
    if (strcmp(role, "professor") == 0) return 1;
    if (strcmp(role, "associate") == 0) return 2;
    if (strcmp(role, "assistant") == 0) return 3;
    return 4;
}

void merge(faculty arr[], int left, int mid, int right) {
    int i = left, j = mid + 1, k = 0;
    faculty temp[right - left + 1];

    while (i <= mid && j <= right) {
        if (arr[i].priority <= arr[j].priority) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    for (int m = 0; m < k; m++) {
        arr[left + m] = temp[m];
    }
}

void mergesort(faculty arr[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergesort(arr, left, mid);
        mergesort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main() {
    int n;
    printf("Enter number of faculty members: ");
    scanf("%d", &n);

    faculty faculty[n];
    int r;

    for (int i = 0; i < n; i++) {
        printf("Faculty %d name: ", i + 1);
        scanf("%s", faculty[i].name);
        printf("Faculty %d role (1=professor, 2=associate, 3=assistant): ", i + 1);
        scanf("%d", &r);

        if (r == 1) strcpy(faculty[i].role, "professor");
        else if (r == 2) strcpy(faculty[i].role, "associate");
        else if (r == 3) strcpy(faculty[i].role, "assistant");
        else {
            printf("Invalid role\n");
            return 1;
        }

        faculty[i].priority = getpriority(faculty[i].role);
    }

    mergesort(faculty, 0, n - 1);

    int i = 0;
    printf("\nArranged Faculty Hierarchy:\n");
    while (i < n) {
        if (faculty[i].priority == 1) {
            printf("Professor: %s\n", faculty[i].name);
            i++;
            for (int j = 0; j < 2 && i < n && faculty[i].priority == 2; j++) {
                printf("  Associate: %s\n", faculty[i].name);
                i++;
                for (int k = 0; k < 2 && i < n && faculty[i].priority == 3; k++) {
                    printf("    Assistant: %s\n", faculty[i].name);
                    i++;
                }
            }
        } else {
            i++; // skip if role is orphaned (e.g., assistant with no parent)
        }
    }

    return 0;
}
