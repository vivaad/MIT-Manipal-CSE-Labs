#include<stdio.h> 
#include<stdlib.h> 

struct Node { 
    int key; 
    struct Node *left; 
    struct Node *right; 
    int height; 
}; 

int idx = 0;

// Get height of node
int height(struct Node *N) { 
    if (N == NULL) 
        return 0; 
    return N->height; 
}

// Maximum of two integers
int max(int a, int b) { 
    return (a > b)? a : b; 
}

// Create new node
struct Node* newNode(int key) { 
    struct Node* node = (struct Node*)malloc(sizeof(struct Node)); 
    node->key = key; 
    node->left = NULL; 
    node->right = NULL; 
    node->height = 1;
    return node; 
}

// Right rotation
struct Node *rightRotate(struct Node *y) { 
    struct Node *x = y->left; 
    struct Node *T2 = x->right; 
    x->right = y; 
    y->left = T2; 
    y->height = max(height(y->left), height(y->right)) + 1; 
    x->height = max(height(x->left), height(x->right)) + 1; 
    return x; 
}

// Left rotation
struct Node *leftRotate(struct Node *x) { 
    struct Node *y = x->right; 
    struct Node *T2 = y->left; 
    y->left = x; 
    x->right = T2; 
    x->height = max(height(x->left), height(x->right)) + 1; 
    y->height = max(height(y->left), height(y->right)) + 1; 
    return y; 
}

// Get balance factor of node
int getBalance(struct Node *N) { 
    if (N == NULL) 
        return 0; 
    return height(N->left) - height(N->right); 
}

// Insert node
struct Node* insert(struct Node* node, int key) { 
    if (node == NULL) 
        return(newNode(key)); 

    if (key < node->key) 
        node->left = insert(node->left, key); 
    else if (key > node->key) 
        node->right = insert(node->right, key); 
    else
        return node; 

    node->height = 1 + max(height(node->left), height(node->right)); 

    int balance = getBalance(node); 

    if (balance > 1 && key < node->left->key) 
        return rightRotate(node); 
    if (balance < -1 && key > node->right->key) 
        return leftRotate(node); 

    if (balance > 1 && key > node->left->key) { 
        node->left = leftRotate(node->left); 
        return rightRotate(node); 
    } 

    if (balance < -1 && key < node->right->key) { 
        node->right = rightRotate(node->right); 
        return leftRotate(node); 
    } 

    return node; 
}

// In-order traversal of AVL tree, stores values in array
void inOrder(struct Node* root, int* arr, int* idx) { 
    if (root != NULL) { 
        inOrder(root->left, arr, idx);
        arr[(*idx)++] = root->key;  // Store key in array
        inOrder(root->right, arr, idx); 
    }
}

// Function to find predecessor and successor
void preSuc(int* arr, int n, int key) {
    int i;
    for(i = 0; i < n; i++) {
        if(arr[i] == key)
            break;
    }

    if(i == 0) {
        printf("No predecessor \n");    
        printf("Successor : %d \n", arr[i+1]);
        return;
    }
    if(i == n-1) {
        printf("No Successor \n");    
        printf("Predecessor : %d \n", arr[i-1]);
        return;
    }

    printf("Predecessor : %d \n", arr[i-1]);
    printf("Successor : %d \n", arr[i+1]);
    return;
}

int main() { 
    struct Node *root = NULL; 
    int n = 0;
    int ch = 0;

    // Inserting nodes into the AVL tree
    root = insert(root, 10); 
    root = insert(root, 20); 
    root = insert(root, 30); 
    root = insert(root, 40); 
    root = insert(root, 50); 
    root = insert(root, 25); 

    // Count the number of nodes in the AVL tree (in-order traversal count)
    int* arr = (int*)malloc(6 * sizeof(int));  // Maximum size based on number of nodes
    int idx = 0;
    inOrder(root, arr, &idx);  // Store in-order traversal in array

    // Print predecessor and successor for the key 30
    preSuc(arr, idx, 30);

    free(arr);  // Free allocated memory
    return 0; 
}
