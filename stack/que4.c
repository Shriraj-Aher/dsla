// WAP to accept a string from user and perform following operations on it
// using stacks. A. Palindrome B. String Reverse C. String Concat D.String
// compare

#include <stdio.h>
#include <string.h>
#define MAX 100

char stack[MAX];
int top = -1;

void push(char ch) {
    if (top < MAX - 1) {
        stack[++top] = ch;
    }
}

char pop() {
    if (top >= 0) {
        return stack[top--];
    }
    return '\0';
}

void reverseString(char str[]) {
    top = -1;
    for (int i = 0; str[i]; i++) {
        push(str[i]);
    }
    printf("Reversed String: ");
    while (top >= 0) {
        printf("%c", pop());
    }
    printf("\n");
}

void checkPalindrome(char str[]) {
    top = -1;
    for (int i = 0; str[i]; i++) {
        push(str[i]);
    }

    int isPalindrome = 1;
    for (int i = 0; str[i]; i++) {
        if (str[i] != pop()) {
            isPalindrome = 0;
            break;
        }
    }

    if (isPalindrome)
        printf("Palindrome: Yes\n");
    else
        printf("Palindrome: No\n");
}

void stringConcat(char str1[], char str2[]) {
    char result[MAX];
    strcpy(result, str1);
    strcat(result, str2);
    printf("Concatenated String: %s\n", result);
}

void stringCompare(char str1[], char str2[]) {
    if (strcmp(str1, str2) == 0)
        printf("Strings are Equal\n");
    else
        printf("Strings are Not Equal\n");
}

int main() {
    char str1[MAX], str2[MAX];
    int choice;

    printf("Enter a string: ");
    gets(str1);  // For simplicity, avoids scanf issues

    while (1) {
        printf("\nMenu:\n");
        printf("1. Check Palindrome\n");
        printf("2. Reverse String\n");
        printf("3. Concatenate with Another String\n");
        printf("4. Compare with Another String\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // Consume leftover newline

        switch (choice) {
            case 1:
                checkPalindrome(str1);
                break;

            case 2:
                reverseString(str1);
                break;

            case 3:
                printf("Enter another string: ");
                gets(str2);
                stringConcat(str1, str2);
                break;

            case 4:
                printf("Enter another string: ");
                gets(str2);
                stringCompare(str1, str2);
                break;

            case 5:
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
