#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

void calculateAvailable(int Total[], int Allocation[][MAX_RESOURCES],
                        int Available[], int n, int m)
{
    for (int j = 0; j < m; j++)
    {
        Available[j] = Total[j];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            Available[j] -= Allocation[i][j];
        }
    }
}

void printState(int Allocation[][MAX_RESOURCES], int Request[][MAX_RESOURCES],
                int Work[], bool Finish[], int n, int m, int iter)
{
    printf("\nIteration %d - Work: ", iter);
    for (int j = 0; j < m; j++)
        printf("%d ", Work[j]);
    printf("\n");

    printf("Process\tAllocation\tRequest\t\tFinish\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t", i);
        // Allocation
        for (int j = 0; j < m; j++)
            printf("%d ", Allocation[i][j]);
        printf("\t\t");
        // Request
        for (int j = 0; j < m; j++)
            printf("%d ", Request[i][j]);
        printf("\t\t");
        // Finish
        printf("%s", Finish[i] ? "true" : "false");
        printf("\n");
    }
}

void detectDeadlock(int Allocation[][MAX_RESOURCES], int Request[][MAX_RESOURCES],
                    int Available[], int n, int m)
{
    int Work[MAX_RESOURCES];
    bool Finish[MAX_PROCESSES];
    int deadlockProcesses[MAX_PROCESSES];
    int deadlockCount = 0;
    int iteration = 0;

    // Initialize
    for (int i = 0; i < m; i++)
        Work[i] = Available[i];
    for (int i = 0; i < n; i++)
        Finish[i] = false;

    // Initial state
    printf("\nInitial State:");
    printState(Allocation, Request, Work, Finish, n, m, iteration++);

    bool found;
    do
    {
        found = false;
        for (int i = 0; i < n; i++)
        {
            if (!Finish[i])
            {
                bool canProceed = true;
                for (int j = 0; j < m; j++)
                {
                    if (Request[i][j] > Work[j])
                    {
                        canProceed = false;
                        break;
                    }
                }

                if (canProceed)
                {
                    printf("\nProcess P%d can proceed. Releasing resources: ", i);
                    for (int j = 0; j < m; j++)
                    {
                        printf("%d ", Allocation[i][j]);
                        Work[j] += Allocation[i][j];
                    }
                    Finish[i] = true;
                    found = true;

                    // Show state after release
                    printState(Allocation, Request, Work, Finish, n, m, iteration++);
                    break; // Restart from P0
                }
            }
        }
    } while (found);

    // Check for deadlock
    deadlockCount = 0;
    for (int i = 0; i < n; i++)
    {
        if (!Finish[i])
        {
            deadlockProcesses[deadlockCount++] = i;
        }
    }

    if (deadlockCount > 0)
    {
        printf("\nDeadlock detected in processes: ");
        for (int i = 0; i < deadlockCount; i++)
            printf("P%d ", deadlockProcesses[i]);
    }
    else
    {
        printf("\nNo deadlock detected.");
    }
    printf("\n");
}

int main()
{
    int n, m;
    int Allocation[MAX_PROCESSES][MAX_RESOURCES];
    int Request[MAX_PROCESSES][MAX_RESOURCES];
    int Total[MAX_RESOURCES];
    int Available[MAX_RESOURCES];

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resource types: ");
    scanf("%d", &m);

    printf("\nEnter Total resources vector:\n");
    for (int j = 0; j < m; j++)
    {
        printf("R%d: ", j);
        scanf("%d", &Total[j]);
    }

    printf("\nEnter Allocation matrix:\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d: ", i);
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &Allocation[i][j]);
        }
    }

    printf("\nEnter Request matrix:\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d: ", i);
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &Request[i][j]);
        }
    }

    calculateAvailable(Total, Allocation, Available, n, m);
    detectDeadlock(Allocation, Request, Available, n, m);

    return 0;
}