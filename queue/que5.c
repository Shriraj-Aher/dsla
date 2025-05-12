// Write a program which simulates the operation of a busy airport which
// has only two runways to handle all takeoffs and landings. You may
// assume that each takeoff or landing takes 15 minutes to complete. One
// runway request is made during each five minute time interval and
// likelihood of landing request is the same as for takeoff. Priority is given
// to planes requesting a landing. If a request cannot be honored it is added
// to a takeoff or landing queue. Your program should simulate 120
// minutes of activity at the airport. Each request for runway clearance
// should be time­stamped and added to the appropriate queue. The output
// from your program should include the final queue contents, the number
// of take offs completed, the number of landings completed, and the
// average number of minutes spent in each queue.



#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIMULATION_TIME 120
#define INTERVAL 5
#define OPERATION_TIME 15
#define MAX_REQUESTS (SIMULATION_TIME / INTERVAL)

typedef struct {
    int request_time;
    int id;
} Plane;

typedef struct {
    Plane planes[100];
    int front, rear;
} Queue;

void initQueue(Queue* q) {
    q->front = q->rear = -1;
}

int isEmpty(Queue* q) {
    return q->front == -1 || q->front > q->rear;
}

void enqueue(Queue* q, int time, int id) {
    if (q->rear == 99) return; // Queue full
    if (q->front == -1) q->front = 0;
    q->rear++;
    q->planes[q->rear].request_time = time;
    q->planes[q->rear].id = id;
}

Plane dequeue(Queue* q) {
    return q->planes[q->front++];
}

int queueLength(Queue* q) {
    return isEmpty(q) ? 0 : q->rear - q->front + 1;
}

int main() {
    Queue takeoffQueue, landingQueue;
    initQueue(&takeoffQueue);
    initQueue(&landingQueue);

    int runway[2] = {0, 0}; // Time until runway is free
    int time, totalTakeoffs = 0, totalLandings = 0;
    int totalTakeoffWait = 0, totalLandingWait = 0;
    int planeId = 1;

    srand(time(0));

    for (time = 0; time <= SIMULATION_TIME; time += INTERVAL) {
        // Randomly generate a request: 0 = takeoff, 1 = landing
        int requestType = rand() % 2;

        if (requestType == 0)
            enqueue(&takeoffQueue, time, planeId++);
        else
            enqueue(&landingQueue, time, planeId++);

        // Try to use the runways
        for (int i = 0; i < 2; i++) {
            if (runway[i] <= time) {
                if (!isEmpty(&landingQueue)) {
                    Plane p = dequeue(&landingQueue);
                    printf("Time %d: Landing plane %d on runway %d\n", time, p.id, i + 1);
                    totalLandingWait += (time - p.request_time);
                    totalLandings++;
                    runway[i] = time + OPERATION_TIME;
                } else if (!isEmpty(&takeoffQueue)) {
                    Plane p = dequeue(&takeoffQueue);
                    printf("Time %d: Taking off plane %d on runway %d\n", time, p.id, i + 1);
                    totalTakeoffWait += (time - p.request_time);
                    totalTakeoffs++;
                    runway[i] = time + OPERATION_TIME;
                }
            }
        }
    }

    // Final report
    printf("\n--- Simulation Summary ---\n");
    printf("Total takeoffs completed: %d\n", totalTakeoffs);
    printf("Total landings completed: %d\n", totalLandings);

    printf("Average takeoff wait time: %.2f minutes\n",
           totalTakeoffs ? (float)totalTakeoffWait / totalTakeoffs : 0.0);
    printf("Average landing wait time: %.2f minutes\n",
           totalLandings ? (float)totalLandingWait / totalLandings : 0.0);

    printf("\nRemaining in takeoff queue (%d planes):\n", queueLength(&takeoffQueue));
    for (int i = takeoffQueue.front; i <= takeoffQueue.rear; i++)
        printf("Plane %d requested at %d minutes\n",
               takeoffQueue.planes[i].id, takeoffQueue.planes[i].request_time);

    printf("\nRemaining in landing queue (%d planes):\n", queueLength(&landingQueue));
    for (int i = landingQueue.front; i <= landingQueue.rear; i++)
        printf("Plane %d requested at %d minutes\n",
               landingQueue.planes[i].id, landingQueue.planes[i].request_time);

    return 0;
}
