// WAP to accept a string of parenthesis and check its validity by using
// stack.

#include<stdio.h>
#include<string.h>
#define MAX 100
char stack[MAX];
int top = -1;

void push(char ch){
    if(top == MAX - 1){
        printf("stack overflow\n");
        return;
    }
    top++;
    stack[top] = ch;
}

char pop(){
    if(top == -1){
        printf("stack is empty");
        return '\0';
    }
    return stack[top--];
}

char peek(){
    if(top == -1) return '\0';
    return stack[top];
}

int isvalid(char expr[]){
    for(int i = 0; i<strlen(expr); i++){
        char current = expr[i];

        if(current =='(' || current == '{' || current == '['){
            push(current);
        }

        else if (current == ')' || current == '}' || current == ']')
        {
            char last = peek();
            if((current == ')' && last == '(') || (current == '}' && last == '{') || (current == ']' && last == '[')){
                pop();
            }
            else{
                return 0;
            }
        }
            
        }
        return top == -1;
        
    }

    
    int main() {
        char expr[MAX];
        printf("Enter a string of parentheses, braces, and brackets: ");
        scanf("%s", expr);
    
        if (isvalid(expr)) {
            printf("The string is VALID.\n");
        } else {
            printf("The string is INVALID.\n");
        }
    
        return 0;
    }