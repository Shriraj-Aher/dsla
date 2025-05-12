// You have to maintain information for a shop owner. For each of the
// products sold in his/hers shop the following information is kept: a
// unique code, a name, a price, amount in stock, date received, expiration
// date. For keeping track of its stock, the clerk would use a computer
// program based on a search tree data structure. Write a program to help
// this person, by implementing the following operations: • Insert an item
// with all its associated data. • List expired items in Prefix order of their names. • List all items. • Delete an item given by its code. • Delete all
// expired items.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Date {
    int day, month, year;
} Date;

typedef struct Product {
    int code;
    char name[50];
    float price;
    int stock;
    Date received, expiry;
    struct Product *left, *right;
} Product;

// Create date
Date createDate(int d, int m, int y) {
    Date dt = {d, m, y};
    return dt;
}

// Check if d1 > d2
int isAfter(Date d1, Date d2) {
    if (d1.year != d2.year) return d1.year > d2.year;
    if (d1.month != d2.month) return d1.month > d2.month;
    return d1.day > d2.day;
}

// Check if expired
int isExpired(Date expiry, Date today) {
    return isAfter(today, expiry);
}

// Create product
Product* createProduct(int code, char name[], float price, int stock, Date r, Date e) {
    Product* p = (Product*)malloc(sizeof(Product));
    p->code = code;
    strcpy(p->name, name);
    p->price = price;
    p->stock = stock;
    p->received = r;
    p->expiry = e;
    p->left = p->right = NULL;
    return p;
}

// Insert by code
Product* insert(Product* root, Product* p) {
    if (!root) return p;
    if (p->code < root->code)
        root->left = insert(root->left, p);
    else if (p->code > root->code)
        root->right = insert(root->right, p);
    return root;
}

// Inorder list
void listAll(Product* root) {
    if (!root) return;
    listAll(root->left);
    printf("Code: %d | Name: %s | Price: %.2f | Stock: %d | Exp: %02d/%02d/%04d\n",
        root->code, root->name, root->price, root->stock,
        root->expiry.day, root->expiry.month, root->expiry.year);
    listAll(root->right);
}

// Preorder expired
void listExpired(Product* root, Date today) {
    if (!root) return;
    if (isExpired(root->expiry, today))
        printf("EXPIRED -> Code: %d | Name: %s | Exp: %02d/%02d/%04d\n",
            root->code, root->name,
            root->expiry.day, root->expiry.month, root->expiry.year);
    listExpired(root->left, today);
    listExpired(root->right, today);
}

// Find min node
Product* minNode(Product* node) {
    while (node && node->left)
        node = node->left;
    return node;
}

// Delete by code
Product* deleteByCode(Product* root, int code) {
    if (!root) return NULL;
    if (code < root->code)
        root->left = deleteByCode(root->left, code);
    else if (code > root->code)
        root->right = deleteByCode(root->right, code);
    else {
        if (!root->left) {
            Product* temp = root->right;
            free(root);
            return temp;
        }
        if (!root->right) {
            Product* temp = root->left;
            free(root);
            return temp;
        }
        Product* temp = minNode(root->right);
        *root = *temp;
        root->right = deleteByCode(root->right, temp->code);
    }
    return root;
}

// Delete all expired
Product* deleteExpired(Product* root, Date today) {
    if (!root) return NULL;
    root->left = deleteExpired(root->left, today);
    root->right = deleteExpired(root->right, today);
    if (isExpired(root->expiry, today))
        root = deleteByCode(root, root->code);
    return root;
}

// --- MAIN ---
int main() {
    Product* root = NULL;
    Date today;
    int choice, code, stock, d, m, y;
    float price;
    char name[50];

    printf("Enter today's date (dd mm yyyy): ");
    scanf("%d %d %d", &d, &m, &y);
    today = createDate(d, m, y);

    while (1) {
        printf("\n1. Add Product\n2. List All\n3. List Expired\n4. Delete by Code\n5. Delete Expired\n6. Exit\nChoice: ");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            printf("Code: "); scanf("%d", &code);
            printf("Name: "); scanf(" %[^\n]", name);
            printf("Price: "); scanf("%f", &price);
            printf("Stock: "); scanf("%d", &stock);
            printf("Received date (dd mm yyyy): "); scanf("%d %d %d", &d, &m, &y);
            Date r = createDate(d, m, y);
            printf("Expiry date (dd mm yyyy): "); scanf("%d %d %d", &d, &m, &y);
            Date e = createDate(d, m, y);
            root = insert(root, createProduct(code, name, price, stock, r, e));
            break;
        case 2:
            listAll(root);
            break;
        case 3:
            listExpired(root, today);
            break;
        case 4:
            printf("Enter code to delete: "); scanf("%d", &code);
            root = deleteByCode(root, code);
            break;
        case 5:
            root = deleteExpired(root, today);
            printf("Expired items deleted.\n");
            break;
        case 6:
            return 0;
        default:
            printf("Invalid choice.\n");
        }
    }
}
