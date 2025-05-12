// WAP to implement following by using stack. A. Factorial of a given
// number B. Generation of Fibonacci series

#include<stdio.h>
#define MAX 100

typedef struct{
    int data[MAX];
    int top;
}stack;

void initstack(stack *s){
    s->top = -1;
}

int isEmpty(stack *s){
    return s->top == -1;
}

void push(stack *s, int data){
    if(s->top == MAX-1){
        printf("stack is full\n");
        return;
    }
    s->top++;
    s->data[s->top] = data;
}

int pop(stack *s){
    if(isEmpty(s)){
        printf("stack is empty\n");
        return -1;
    }
    int x = s->data[s->top];
    s->top--;
    return x;
}

int factorial_stack(int n){
    stack s;
    initstack(&s);

    for(int i=n; i>=1; i--){
        push(&s, i);
    }

    int result = 1;
    while (!isEmpty(&s))
    {
        result = result*pop(&s);
    }
    return result;
}

void fibonacci_stack(int terms){
    stack s;
    initstack(&s);

    int a=0, b=1;
    printf("Fibonacci series: ");
    if(terms >= 1){
        printf("%d ", a);
        push(&s, a);
    }

    if(terms >= 2){
        printf("%d ", b);
        push(&s, b); 
    }

    for(int i=3; i<=terms; i++){
        int secondLast = pop(&s);
        int firstlast = pop(&s);
        int next = firstlast + secondLast;

        printf("%d ", next);

        push(&s, secondLast);
        push(&s, next);
    }
    printf("\n");
}

int main(){
    int choice, num;

    printf("menu: \n");
    printf("1. Factorial of number \n");
    printf("2. Fibonacci series \n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch(choice){
        case 1:
        printf("enter the number to find factorial: ");
        scanf("%d", &num);
        printf("factorial of %d is %d\n", num, factorial_stack(num));
        break;
        case 2:
        printf("enter the number of terms in fibonacci series: ");
        scanf("%d", &num);
        fibonacci_stack(num);
        break;
        default:
        printf("invalid choice");
        break;
    }

    return 0;
}
