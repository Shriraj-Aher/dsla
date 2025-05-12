Write a program to illustrate operations on a BST holding numeric keys.

The menu must include: • Insert • Delete • Find • Show



#include <stdio.h>
#include <stdlib.h>

// Structure for BST node
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Function to create a new BST node
TreeNode* createNode(int value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Non-recursive Insert operation
TreeNode* insertNode(TreeNode* root, int value) {
    TreeNode* newNode = createNode(value);
    if (root == NULL) {
        return newNode;
    }

    TreeNode* current = root;
    TreeNode* parent = NULL;

    while (current != NULL) {
        parent = current;
        if (value < current->data) {
            current = current->left;
        } else if (value > current->data) {
            current = current->right;
        } else {
            printf("Value %d already exists in BST\n", value);
            free(newNode);
            return root;
        }
    }

    if (value < parent->data) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    return root;
}

// Helper function to find minimum value node (used in delete)
TreeNode* findMinNode(TreeNode* node) {
    while (node && node->left != NULL) {
        node = node->left;
    }
    return node;
}

// Non-recursive Delete operation
TreeNode* deleteNode(TreeNode* root, int value) {
    if (root == NULL) {
        printf("Value %d not found in BST\n", value);
        return root;
    }

    TreeNode* current = root;
    TreeNode* parent = NULL;

    // Find the node to be deleted
    while (current != NULL && current->data != value) {
        parent = current;
        if (value < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current == NULL) {
        printf("Value %d not found in BST\n", value);
        return root;
    }

    // Node with only one child or no child
    if (current->left == NULL) {
        TreeNode* temp = current->right;
        if (parent == NULL) {
            free(current);
            return temp;
        }
        if (parent->left == current) {
            parent->left = temp;
        } else {
            parent->right = temp;
        }
        free(current);
    } else if (current->right == NULL) {
        TreeNode* temp = current->left;
        if (parent == NULL) {
            free(current);
            return temp;
        }
        if (parent->left == current) {
            parent->left = temp;
        } else {
            parent->right = temp;
        }
        free(current);
    } else {
        // Node with two children: Get inorder successor (smallest in right subtree)
        TreeNode* successor = findMinNode(current->right);
        int tempData = successor->data;
        root = deleteNode(root, successor->data);
        current->data = tempData;
    }

    return root;
}

// Non-recursive Find operation
void findNode(TreeNode* root, int value) {
    TreeNode* current = root;
    while (current != NULL) {
        if (value == current->data) {
            printf("Value %d found in BST\n", value);
            return;
        } else if (value < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    printf("Value %d not found in BST\n", value);
}

// Structure for stack used in non-recursive traversals
typedef struct StackNode {
    TreeNode* treeNode;
    struct StackNode* next;
} StackNode;

// Stack operations for non-recursive traversal
void push(StackNode** top, TreeNode* treeNode) {
    StackNode* newStackNode = (StackNode*)malloc(sizeof(StackNode));
    if (newStackNode == NULL) {
        printf("Stack overflow\n");
        exit(1);
    }
    newStackNode->treeNode = treeNode;
    newStackNode->next = *top;
    *top = newStackNode;
}

TreeNode* pop(StackNode** top) {
    if (*top == NULL) {
        return NULL;
    }
    StackNode* temp = *top;
    TreeNode* poppedNode = temp->treeNode;
    *top = (*top)->next;
    free(temp);
    return poppedNode;
}

int isStackEmpty(StackNode* top) {
    return top == NULL;
}

// Non-recursive Inorder Traversal (for Show operation)
void inorderTraversal(TreeNode* root) {
    if (root == NULL) {
        printf("BST is empty\n");
        return;
    }

    StackNode* stack = NULL;
    TreeNode* current = root;

    printf("BST elements (inorder): ");
    while (current != NULL || !isStackEmpty(stack)) {
        // Reach the leftmost node of the current node
        while (current != NULL) {
            push(&stack, current);
            current = current->left;
        }

        // Current must be NULL at this point
        current = pop(&stack);
        printf("%d ", current->data);

        // Now visit the right subtree
        current = current->right;
    }
    printf("\n");
}

// Function to display menu
void displayMenu() {
    printf("\nBST Operations Menu:\n");
    printf("1. Insert a value\n");
    printf("2. Delete a value\n");
    printf("3. Find a value\n");
    printf("4. Show BST (inorder traversal)\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    TreeNode* root = NULL;
    int choice, value;

    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insertNode(root, value);
                break;
            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                root = deleteNode(root, value);
                break;
            case 3:
                printf("Enter value to find: ");
                scanf("%d", &value);
                findNode(root, value);
                break;
            case 4:
                inorderTraversal(root);
                break;
            case 5:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 5);

    // TODO: Add code to free the BST memory

    return 0;
}