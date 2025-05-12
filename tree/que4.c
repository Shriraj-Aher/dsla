// You have to maintain information for a shop owner. For each of the
// products sold in his/hers shop the following information is kept: a
// unique code, a name, a price, amount in stock, date received, expiration
// date. For keeping track of its stock, the clerk would use a computer
// program based on a search tree data structure. Write a program to help
// this person, by implementing the following operations: • Insert an item
// with all its associated data. • Find an item by its code, and support
// updating of the item found. • List valid items in lexicographic order of
// their names.



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define structure for date
typedef struct {
    int day, month, year;
} Date;

// Define structure for product
typedef struct Product {
    char code[20];         // Unique code
    char name[50];         // Product name
    float price;           // Price
    int stock;             // Amount in stock
    Date received;
    Date expiry;

    struct Product *left, *right;  // BST pointers
} Product;

// Function to compare two dates
int isExpired(Date d1, Date today) {
    if (d1.year < today.year) return 1;
    if (d1.year == today.year && d1.month < today.month) return 1;
    if (d1.year == today.year && d1.month == today.month && d1.day < today.day) return 1;
    return 0;
}

// Create a new product node
Product* createProduct() {
    Product p = (Product)malloc(sizeof(Product));

    printf("Enter product code: ");
    scanf("%s", p->code);
    printf("Enter product name: ");
    scanf(" %[^\n]", p->name);
    printf("Enter price: ");
    scanf("%f", &p->price);
    printf("Enter stock amount: ");
    scanf("%d", &p->stock);

    printf("Enter received date (dd mm yyyy): ");
    scanf("%d%d%d", &p->received.day, &p->received.month, &p->received.year);

    printf("Enter expiry date (dd mm yyyy): ");
    scanf("%d%d%d", &p->expiry.day, &p->expiry.month, &p->expiry.year);

    p->left = p->right = NULL;
    return p;
}

// Insert product into BST by name
Product* insert(Product *root, Product *newProd) {
    if (root == NULL) return newProd;

    if (strcmp(newProd->name, root->name) < 0)
        root->left = insert(root->left, newProd);
    else
        root->right = insert(root->right, newProd);

    return root;
}

// Search product by code and update it
void searchAndUpdate(Product *root, char code[]) {
    if (root == NULL) {
        printf("Product not found.\n");
        return;
    }

    if (strcmp(root->code, code) == 0) {
        printf("Product found: %s\n", root->name);
        printf("Enter new price: ");
        scanf("%f", &root->price);
        printf("Enter new stock: ");
        scanf("%d", &root->stock);
        return;
    }

    searchAndUpdate(root->left, code);
    searchAndUpdate(root->right, code);
}

// In-order traversal to list valid (not expired) items
void listValidItems(Product *root, Date today) {
    if (root == NULL) return;

    listValidItems(root->left, today);

    if (!isExpired(root->expiry, today)) {
        printf("Name: %s | Code: %s | Price: %.2f | Stock: %d\n", root->name, root->code, root->price, root->stock);
    }

    listValidItems(root->right, today);
}

// Main menu
int main() {
    Product *root = NULL;
    int choice;
    char searchCode[20];
    Date today = {12, 5, 2025}; // You can change this to the current date

    while (1) {
        printf("\n1. Insert Product\n2. Search & Update by Code\n3. List Valid Products\n4. Exit\nChoice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            Product *p = createProduct();
            root = insert(root, p);
        }
        else if (choice == 2) {
            printf("Enter code to search: ");
            scanf("%s", searchCode);
            searchAndUpdate(root, searchCode);
        }
        else if (choice == 3) {
            printf("\nValid products:\n");
            listValidItems(root, today);
        }
        else if (choice == 4) {
            break;
        }
        else {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}