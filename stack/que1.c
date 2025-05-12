// infix to postfix
#include<stdio.h>
#define MAX 50
char stack[MAX];
int top = -1;

int isEmpty(){
if(top == -1) return 1;
else return 0;
}

void push(char x){
    if(top < MAX-1){
        top++;
        stack[top] = x;
    }
}

char pop(){
    if(top >= 0){
        char ch = stack[top];
        top--;
        return ch;
    }
    return '\0';
}

char peek(){
    if(top >= 0){
        return stack[top];
    }
    else{
        return '\0';
    }
}

int isoperand(char c){
    if(c >= 'A' && c<= 'Z' || c>= 'a' && c<= 'z' || c>= '0' && c<= '9')
    return 1;
    else
    return 0;
}

int isoperator(char c){
    if(c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
    return 1;
    else
    return 0;
}

int precedence(char c){
    if(c == '^') return 3;
    if(c == '/' || c == '*') return 2;
    if(c == '+' || c == '-') return 1;
    else return 0;
}

void infixtopostfix(char infix[], char postfix[]){
    int i,j;
    i = j = 0;
    for(int i=0; infix[i] != '\0'; i++){
        char c = infix[i];
        if(isoperand(c)){
            postfix[j] = c;
            j++;
        }
        else if(c == '('){
            push(c);
        }
        else if(c == ')'){
            while(!isEmpty() && peek() != '('){
                postfix[j] = pop();
                j++;
            }
            pop(); // to pop (     // stack = * // + 
        }
        else if(isoperator(c)){
            while(!isEmpty() && precedence(peek()) >= precedence(c)){
                postfix[j] = pop();
                j++;
            }
            push(c);
        }

        
    }

    while(!isEmpty()){
        postfix[j] = pop();
        j++;
    }
    postfix[j] = '\0';
}

int main(){
    char infix[MAX], postfix[MAX];

    printf("enter the infix expression: ");
    scanf("%s",infix);

    infixtopostfix(infix, postfix);

    printf("Postfix expression is : %s",postfix);

}