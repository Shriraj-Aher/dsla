// Given a set of points Pi , 1 ? i ? N (? 2) on the x­axis, find Pi and P j
// such that |Pi ? P j | is minimum. e.g. P1 | P2 | P3 | P4 | P5 | P6 {P4 , P6}
// is the closest pair.


#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    printf("Enter number of points: ");
    scanf("%d", &n);

    if (n < 2) {
        printf("At least 2 points are required.\n");
        return 0;
    }

    int points[n];
    printf("Enter the points on x-axis:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &points[i]);
    }

    // Manual Bubble Sort
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (points[j] > points[j + 1]) {
                int temp = points[j];
                points[j] = points[j + 1];
                points[j + 1] = temp;
            }
        }
    }

    // Find the closest pair
    int minDiff = abs(points[1] - points[0]);
    int pi = points[0], pj = points[1];

    for (int i = 1; i < n - 1; i++) {
        int diff = abs(points[i + 1] - points[i]);
        if (diff < minDiff) {
            minDiff = diff;
            pi = points[i];
            pj = points[i + 1];
        }
    }

    printf("\nClosest pair is: {%d, %d} with minimum distance = %d\n", pi, pj, minDiff);

    return 0;
}
