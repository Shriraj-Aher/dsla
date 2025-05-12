// Write a Program to create a Binary Tree and perform following
// nonrecursive operations on it. a. Levelwise display b. Mirror image c.
// Display height of a tree.

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

// Queue for level-order traversal
Node* queue[MAX];
int front = -1, rear = -1;

int isQueueEmpty() {
    return (front == -1 || front > rear);
}

void enqueue(Node* node) {
    if (rear == MAX - 1) return;

    if (front == -1) front = 0;
    queue[++rear] = node;
}

Node* dequeue() {
    if (isQueueEmpty()) return NULL;
    return queue[front++];
}

// Create a new node
Node* createNode(int data) {
    Node* newnode = (Node*)malloc(sizeof(Node));
    newnode->data = data;
    newnode->left = newnode->right = NULL;
    return newnode;
}

// Create binary tree level-wise
Node* createBinaryTree() {
    front = rear = -1;
    int data;
    printf("Enter root node data: ");
    scanf("%d", &data);

    Node* root = createNode(data);
    enqueue(root);

    while (!isQueueEmpty()) {
        Node* current = dequeue();

        printf("Enter left child of %d (-1 for NULL): ", current->data);
        scanf("%d", &data);
        if (data != -1) {
            current->left = createNode(data);
            enqueue(current->left);
        }

        printf("Enter right child of %d (-1 for NULL): ", current->data);
        scanf("%d", &data);
        if (data != -1) {
            current->right = createNode(data);
            enqueue(current->right);
        }
    }

    return root;
}

// (a) Levelwise Display
void levelOrderTraversal(Node* root) {
    if (!root) return;

    front = rear = -1;
    enqueue(root);

    while (!isQueueEmpty()) {
        Node* temp = dequeue();
        printf("%d ", temp->data);

        if (temp->left) enqueue(temp->left);
        if (temp->right) enqueue(temp->right);
    }
}

// (b) Mirror Image (non-recursive)
void mirrorTree(Node* root) {
    if (!root) return;

    front = rear = -1;
    enqueue(root);

    while (!isQueueEmpty()) {
        Node* temp = dequeue();

        // Swap left and right
        Node* t = temp->left;
        temp->left = temp->right;
        temp->right = t;

        if (temp->left) enqueue(temp->left);
        if (temp->right) enqueue(temp->right);
    }
    printf("Tree mirrored successfully.\n");
}

// (c) Height of the tree (non-recursive)
int treeHeight(Node* root) {
    if (!root) return 0;

    front = rear = -1;
    enqueue(root);
    int height = 0;

    while (1) {
        int nodeCount = rear - front + 1;
        if (nodeCount == 0) return height;
        height++;

        while (nodeCount > 0) {
            Node* node = dequeue();
            if (node->left) enqueue(node->left);
            if (node->right) enqueue(node->right);
            nodeCount--;
        }
    }
}

// Main Menu
int main() {
    Node* root = NULL;
    int choice;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Create Binary Tree\n");
        printf("2. Levelwise Display\n");
        printf("3. Mirror Image\n");
        printf("4. Height of Tree\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                root = createBinaryTree();
                break;
            case 2:
                if (!root) {
                    printf("Tree is empty.\n");
                    break;
                }
                printf("Levelwise traversal: ");
                levelOrderTraversal(root);
                printf("\n");
                break;
            case 3:
                if (!root) {
                    printf("Tree is empty.\n");
                    break;
                }
                mirrorTree(root);
                break;
            case 4:
                if (!root) {
                    printf("Tree is empty.\n");
                    break;
                }
                printf("Height of tree: %d\n", treeHeight(root));
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}

