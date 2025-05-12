// Write a menu­driven program that maintains a queue of passengers
// waiting to see a ticket agent. The program user should be able to insert a
// new passenger at the rear of the queue, display the passenger at the front
// of the queue, or remove the passenger at the front of the queue. The
// program will display the number of passengers left in the queue just
// before it terminates.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 100
#define MAX_TIME 120  // Total simulation time in minutes

typedef struct {
    char name[50];
    int servicetime;
} Passenger;

Passenger queue[MAX];
int front = -1, rear = -1;

int isFull() {
    return rear == MAX - 1;
}

int isEmpty() {
    return front == -1 || front > rear;
}

void insertPassenger() {
    if (isFull()) {
        printf("Queue is full! Cannot add more passengers.\n");
        return;
    }

    char name[50];
    printf("Enter passenger name: ");
    scanf(" %[^\n]s", name);

    int time = rand() % 15 + 1; // Random time between 1 and 15

    if (front == -1) front = 0;
    rear++;
    strcpy(queue[rear].name, name);
    queue[rear].servicetime = time;

    printf("Passenger '%s' added with random service time: %d minutes.\n", name, time);
}

void displayFrontPassenger() {
    if (isEmpty()) {
        printf("Queue is empty.\n");
    } else {
        printf("Passenger at front: %s | Service Time: %d minutes\n",
               queue[front].name, queue[front].servicetime);
    }
}

void simulate2HourService() {
    int timeUsed = 0;
    printf("\n--- Starting 2-Hour Simulation ---\n");

    while (!isEmpty() && timeUsed + queue[front].servicetime <= MAX_TIME) {
        printf("Serving passenger: %s (Time: %d minutes)\n",
               queue[front].name, queue[front].servicetime);
        timeUsed += queue[front].servicetime;
        front++;
    }

    printf("\nSimulation complete.\n");
    printf("Total time used: %d minutes\n", timeUsed);
    printf("Passengers left in queue: %d\n", rear - front + 1);
}

void displayQueueCount() {
    if (isEmpty()) {
        printf("No passengers in queue.\n");
    } else {
        printf("Number of passengers left in queue: %d\n", rear - front + 1);
    }
}

int main() {
    int choice;
    srand(time(0));  // Seed the random number generator

    do {
        printf("\n--- Ticket Agent Queue Menu ---\n");
        printf("1. Add passenger to queue\n");
        printf("2. Show front passenger\n");
        printf("3. Simulate 2-hour service\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: insertPassenger(); break;
            case 2: displayFrontPassenger(); break;
            case 3: simulate2HourService(); break;
            case 4:
                displayQueueCount();
                printf("Exiting...\n");
                break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 4);

    return 0;
}
