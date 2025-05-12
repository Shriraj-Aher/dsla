// A person is living in house having 5 rooms. These rooms are adjacent to
// each other. There is a treasure which is electronically locked and to
// unlock it we need a code. In last room there is a box in which some
// decimal number is written. We need to convert that number into binary
// to open treasure which is kept in room no.1 . We need to move from
// room no.1 to 2 to 3 and so on and follow the reverse way to come back
// i.e. from 5 to 4 to 3 etc. Apply suitable logic to implement this scenario
// by using stacks

#include <stdio.h>
#define max 32

typedef struct 
{
    int data[max];
    int top;
}stack;

void init(stack *s){
    s->top =-1;
}

void push(stack *s, int val){
    if(s->top == max - 1){
        printf("stack overflow");
        return;
    }
    s->top++;
    s->data[s->top] = val;
}

int pop(stack *s){
    if(s->top == -1){
        printf("stack empty");
        return -1;
    }
    int x = s->data[s->top];
    s->top--;
    return x;
}

void convert_binary(int dec, stack *s){
    while(dec > 0){
        push(s, dec % 2);
        dec = dec/2;
    }
}

int main(){
    stack s;
    init(&s);

    printf("moving from room 1 to room 5\n");

    int dec;
    printf("you found the box in room 5. enter the decimal number: ");
    scanf("%d", &dec);

    convert_binary(dec, &s);

    printf("converted %d to binary and stored in the stack\n", dec);
    printf("Returning from Room 5 to Room 1...\n");
    printf("Binary code to unlock the treasure in Room 1: ");
while (s.top >= 0) {
    printf("%d", pop(&s));  // Output binary digits in reverse (MSB to LSB)
}

printf("\nTreasure unlocked!\n");
    return 0;
}