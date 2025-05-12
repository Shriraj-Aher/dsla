// You hav e a fleet of N cars waiting for repair, with the estimated repair
// times rk for the car Ci , 1 ? k ? N. What is the best repairschedule (order
// of repairs) to minimize the total lost time for being out­of­service. How
// much computation is needed to find the lost service­times all schedules?

#include<stdio.h>

typedef struct car{      
    int id;
    int rep_time;
}car;

void selection_sort(int n, car c[]){
    for(int i=0; i<n-1; i++){
        int min = i;
        for(int j=i+1; j<n; j++){
            if(c[j].rep_time < c[min].rep_time){
                min = j;
            }
        }
        if(min != i){
            car temp = c[i];
            c[i] = c[min];
            c[min] = temp;
        }
    }
}

int main(){
    int n;
    printf("enter the number of cars: ");
    scanf("%d", &n);

    car c[n];

    for(int i=0; i<n; i++){
        c[i].id = i+1;
        printf("enter the repair time for car %d: ", i+1);
        scanf("%d", &c[i].rep_time);
    }

    selection_sort(n,c);

    printf("\n optimal repair time: \n");
    // for(int i=0; i<n; i++){
    //     printf("car %d - repair time %d\n", c[i].id, c[i].rep_time);
    // }

    int total_time = 0;
    int cumulative_time = 0;
    for(int i=0; i<n; i++){
        cumulative_time += c[i].rep_time;
        total_time += cumulative_time;
        printf("Car %d: Repair time = %d, Cumulative time = %d\n", i + 1, c[i].rep_time, cumulative_time);

    }

    printf("\n minimum total loat time: %d\n", total_time);
    return 0;
}