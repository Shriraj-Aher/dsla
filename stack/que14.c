// Normally we write our name in order of First name, Middle name and
// Surname. We need to accept these three words in a single string. Write a
// program to arrange these three words in order of Surname, First name
// and Middle name using stack only

#include <stdio.h>
#include <string.h>

#define MAX 3
#define WORD_LEN 30

char stack[MAX][WORD_LEN];
int top = -1;

void push(char word[]) {
    if (top < MAX - 1) {
        top++;
        strcpy(stack[top], word);
    }
}

void pop(char word[]) {
    if (top >= 0) {
        strcpy(word, stack[top]);
        top--;
    }
}

int main() {
    char input[100];
    char word[3][WORD_LEN];  // For storing First, Middle, Surname
    int count = 0;

    printf("Enter full name (First Middle Surname): ");
    gets(input);  // Take the full line

    // Split words and push onto stack
    char *token = strtok(input, " ");
    while (token != NULL && count < MAX) {
        push(token);
        token = strtok(NULL, " ");
        count++;
    }

    // Pop in reverse order
    char surname[WORD_LEN], first[WORD_LEN], middle[WORD_LEN];
    pop(surname);
    pop(middle);
    pop(first);

    printf("Reordered Name: %s %s %s\n", surname, first, middle);

    return 0;
}
