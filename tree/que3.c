// Write a program to illustrate operations on a BST holding numeric keys.

// The menu must include: • Insert • Delete • Find • Show



#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left, *right;
};

#define SIZE 100
struct Node* queue[SIZE];
int front = -1, rear = -1;

void enqueue(struct Node* node) {
    if (rear < SIZE - 1) {
        rear = rear + 1;
        queue[rear] = node;
        if (front == -1) 
        front = 0;
    }
}

struct Node* dequeue() {
    if (front == -1 || front > rear) 
    return NULL;
    struct Node* temp = queue[front];
    front = front + 1;
    return temp;
}

int isEmpty() {
    return front == -1 || front > rear;
}

struct Node* insert(struct Node* root, int data) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;

    if (root == NULL)
        return newNode;

    struct Node* current = root;
    struct Node* parent = NULL;

    while (current != NULL) {
        parent = current;
        if (data < current->data)
            current = current->left;
        else
            current = current->right;
    }

    if (data < parent->data)
        parent->left = newNode;
    else
        parent->right = newNode;

    return root;
}

struct Node* findMin(struct Node* root) {
    while (root && root->left)
        root = root->left;
    return root;
}

struct Node* deleteNode(struct Node* root, int key) {
    struct Node *parent = NULL, *curr = root;

    while (curr && curr->data != key) {
        parent = curr;
        if (key < curr->data)
            curr = curr->left;
        else
            curr = curr->right;
    }

    if (curr == NULL) return root; 

    
    if (curr->left == NULL || curr->right == NULL) {
        struct Node* newCurr;

        if (curr->left == NULL)
            newCurr = curr->right;
        else
            newCurr = curr->left;

        if (parent == NULL)
            return newCurr;

        if (curr == parent->left)
            parent->left = newCurr;
        else
            parent->right = newCurr;

        free(curr);
    }

    
    else {
        struct Node* successor = findMin(curr->right);
        int val = successor->data;
        root = deleteNode(root, successor->data);
        curr->data = val;
    }

    return root;
}

void mirror(struct Node* root) {
    if (!root) return;
    front = rear = -1;
    enqueue(root);

    while (!isEmpty()) {
        struct Node* current = dequeue();

       
        struct Node* temp = current->left;
        current->left = current->right;
        current->right = temp;

        if (current->left) enqueue(current->left);
        if (current->right) enqueue(current->right);
    }
}

void levelOrder(struct Node* root) {
    if (!root) return;
    front = rear = -1;
    enqueue(root);

    while (!isEmpty()) {
        struct Node* current = dequeue();
        printf("%d ", current->data);
        if (current->left) enqueue(current->left);
        if (current->right) enqueue(current->right);
    }
    printf("\n");
}

int height(struct Node* root) {
    if (!root) return 0;
    front = rear = -1;
    enqueue(root);
    int level = 0;

    while (1) {
        int nodeCount = rear - front + 1;
        if (nodeCount == 0)
            return level;

        level++;
        while (nodeCount > 0) {
            struct Node* current = dequeue();
            if (current->left) enqueue(current->left);
            if (current->right) enqueue(current->right);
            nodeCount--;
        }
    }
}

void printLeafNodes(struct Node* root) {
    if (!root) return;
    front = rear = -1;
    enqueue(root);

    while (!isEmpty()) {
        struct Node* current = dequeue();
        if (!current->left && !current->right)
            printf("%d ", current->data);
        if (current->left) enqueue(current->left);
        if (current->right) enqueue(current->right);
    }
    printf("\n");
}

int main() {
    struct Node* root = NULL;
    int choice, value;

    while (1) {
        printf("\n BST Operations \n");
        printf("1. Insert\n2. Delete\n3. Mirror\n4. Level-wise Display\n5. Height\n6. Leaf Nodes\n7. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                break;
            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                root = deleteNode(root, value);
                break;
            case 3:
                mirror(root);
                printf("Tree mirrored.\n");
                break;
            case 4:
                printf("Level-wise Display: ");
                levelOrder(root);
                break;
            case 5:
                printf("Height of tree: %d\n", height(root));
                break;
            case 6:
                printf("Leaf Nodes: ");
                printLeafNodes(root);
                break;
            case 7:
                exit(0);
        }
    }

    return 0;
}
