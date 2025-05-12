// Write a Program to create a Binary Tree and perform following
// nonrecursive operations on it. a. Preorder Traversal b. Postorder
// Traversal c. Count total no. of nodes d. Display height of a tree.

#include<stdio.h>
#include<stdlib.h>

#define max 100 
int arr[7];
typedef struct Node{
    int data;
    struct Node *left, *right;
}Node;

Node* stack[max];
int top = -1;

int stackempty(){
    if(top == -1)
    return 1;
    else return 0;
}

void push(Node* x){
    if(top == max-1){
        return;
    }
    else{
        top++;
        stack[top] = x;
    }
}

Node* pop(){
    if(!stackempty()){
        Node* temp = stack[top];
        top--;
        return temp;
    }
    else return NULL;
}

Node* queue[max];
int front = -1;
int rear = -1;

void enqueue(Node* Node){
    if(rear == max-1){
        return;
    }
    else if(rear == -1 && front == -1){
        front = rear = 0;
        queue[rear] = Node;
    }
    else{
        rear++;
        queue[rear] = Node;
    }
}

Node* dequeue(){
    if(front == -1 || front > rear){
        return NULL;
    }
    else{
        Node* temp = queue[front];
        front++;
        return temp;
    }
}

int isqueueempty(){
    return front == -1 || front > rear;
}


Node* createnode(int data){
    Node* newnode = (Node*)malloc(sizeof(Node));
    newnode->data = data;
    newnode->left = newnode->right = NULL;
    return newnode;
}

Node* createBinarytree(){
    front = rear = -1;  // Reset the queue!
    int data;
    printf("enter the root node data: ");
    scanf("%d", &data);
    Node* root = createnode(data);
    enqueue(root);
    int h = 1;

    while(!isqueueempty()){
        Node* current = dequeue();

        printf("enter left child of %d (-1 for null): ", current->data);
        scanf("%d", &data);
        if(data != -1){
            current->left = createnode(data);
            enqueue(current->left);
        }

        printf("enter right child of %d (-1 for null): ", current->data);
        scanf("%d", &data);
        if(data != -1){
            current->right = createnode(data);
            enqueue(current->right);
        }
    }

    return root;
}

int idx =0;

void inorder(Node* root){
    while(root != NULL){
        push(root);
        root = root->left;
    }

    while(!stackempty()){
        root = pop();
        printf("%d ",root->data);
        arr[idx++] = root->data;
        root = root->right;
        while(root != NULL){
            push(root);
            root = root->left;
        }
    }
}

void preorder(Node* root){
    while(root != NULL){
        push(root);
        printf("%d ", root->data);
        root = root->left;
    }

    while (!stackempty())
    {
        root = pop();
        root = root->right;
        while(root != NULL){
            push(root);
            printf("%d ", root->data);
            root = root->left;
        }
    } 
}

void postorder(Node* root){
    Node* prev = NULL;
    while (root != NULL || !stackempty())
    {
        while(root != NULL){
            push(root);
            root = root->left;
        }

        root = stack[top];

        if(root->right == NULL || root->right == prev){
            printf("%d ", root->data);
            pop();
            prev = root;
            root = NULL;
        }
        else{
            root = root->right;
        }
    }
}

int countnodes(Node* root){
    if(!root) return 0;
    int count = 0;
    top = -1;
    push(root);
    while (!stackempty())
    {
        Node* current = pop();
        count++;
        if(current->left) push(current->left);
        if(current->right) push(current->right);
    }
    
    return count;
}

int treeheight(Node* root){
    if(! root) return 0;
    front = rear = -1;
    enqueue(root);
    int height = 0;

    while(1){
        int nodecount = rear - front + 1;
        if(nodecount == 0)
        return height;

        height++;

        while(nodecount > 0){
            Node* node = dequeue();
            if(node->left) enqueue(node->left);
            if(node->right) enqueue(node->right);
            nodecount--;
        }
    }
}

// void mirror(Node* root){
//     inorder(root);
//     int temp[7];
//     int k=6;
//     for(int i=0; i<7; i++){
//         temp[i] = arr[k];
//         k--;
//     }
//     for(int i=0; i<7; i++){
//     root = createBinarytree();
//     }

// }
int main(){
    Node* root = NULL;
    int choice;

    while(1){
        printf("\nMenu: \n");
        printf("1. create binary tree\n");
        printf("2. inorder traversal  \n");
        printf("3. preorder traversal \n");
        printf("4. postorder traversal \n");
        printf("5. count total nodes \n");
        printf("6. hieght of the tree \n");
        printf("7. exit: \n");
        printf("enter choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
            root = createBinarytree();
            break;

            case 2: 
            printf("inorder traversal: \n");
            inorder(root);
            break;

            case 3: 
            printf("preorder traversal: \n");
            preorder(root);
            break;

            case 4:
            printf("postorder traversal: \n");
            postorder(root);
            break;

            case 5:
            printf("total nodes: %d", countnodes(root));
            break;

            case 6:
            printf("height of tree: %d", treeheight(root));
            break;

            case 7:
            exit(0);

            default:
            printf("invalid choice");
        }
    }

    return 0;
}