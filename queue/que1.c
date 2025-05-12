// We Fly Anywhere Airlines (WFAA) is considering redesigning their
// ticket counters for airline passengers. They would like to have two
// separate waiting lines, one for regular customers and one for frequent
// flyers. Assuming there is only one ticket agent available to serve all
// passengers, they would like to determine the average waiting time for
// both types of passengers using various strategies for taking passengers
// from the waiting lines. WAP to simulate this situation.


#include <stdio.h>

#define MAX 10

typedef struct {
    int arrival;
    int service;
} Passenger;

int main() {
    Passenger frequentFlyers[MAX] = {
        {0, 3}, {2, 2}, {4, 1}, {6, 2}, {8, 3}
    };
    Passenger regularCustomers[MAX] = {
        {1, 4}, {3, 2}, {5, 3}, {7, 2}, {9, 1}
    };

    int ffIndex = 0, regIndex = 0;
    int time = 0;
    int ffTotalWait = 0, regTotalWait = 0;
    int ffServed = 0, regServed = 0;

    while (ffIndex < 5 || regIndex < 5) {
        // Check who can be served now
        if (ffIndex < 5 && frequentFlyers[ffIndex].arrival <= time) {
            int wait = time - frequentFlyers[ffIndex].arrival;
            ffTotalWait += wait;
            time += frequentFlyers[ffIndex].service;
            ffServed++;
            ffIndex++;
        }
        else if (regIndex < 5 && regularCustomers[regIndex].arrival <= time) {
            int wait = time - regularCustomers[regIndex].arrival;
            regTotalWait += wait;
            time += regularCustomers[regIndex].service;
            regServed++;
            regIndex++;
        }
        else {
            time++; // No one is ready yet, advance time
        }
    }

    printf("Average waiting time for Frequent Flyers: %.2f\n", (float)ffTotalWait / ffServed);
    printf("Average waiting time for Regular Customers: %.2f\n", (float)regTotalWait / regServed);

    return 0;
}
