// Assume that an array A with n elements was sorted in an ascending
// order, but two of its elements swapped their positions by a mistake while
// maintaining the array. Write a code to identify the swapped pair of
// elements and their positions in the asymptotically best possible time.
// \[Assume that all given elements are distinct integers.]

#include<stdio.h>

void findswapped(int arr[], int n){
    int x = -1;
    int y = -1;

    for(int i=0; i<n-1; i++){            // 1, 2, 6, 4, 5, 3 
        if(arr[i] > arr[i+1]){           // 0, 1, 2, 3, 4, 5  // i = 0, 1, 2, 3, 4 
                                                            //   y = 1, 2, 2, 4, 5
            if( x == -1){                                    //  x= -1, -1, 2, 2, 2
                x = i;
            }
            else{
                y = i+1;
            }
        }
    }

    if(y == -1)
    y = x+1;

    printf("swapped elements: %d and %d\n", arr[x], arr[y]);
    printf("their positions: %d and %d\n", x, y);
}

int main(){
    int arr[] = {1, 2, 6, 4, 5, 3, 7};
    int n = sizeof(arr)/sizeof(arr[0]);
    findswapped(arr, n);
    return 0;
}