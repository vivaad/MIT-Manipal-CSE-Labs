#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *left, *right;
} Node;

Node* create_node(int data) {
    Node* cur = (Node*)malloc(sizeof(Node));
    cur->data = data;
    cur->left = cur->right = NULL;
    return cur;
}

Node* insert(Node* root, int data) {
    if (root == NULL) {
        return create_node(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    return root;
}

Node* search(Node* root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }
    if (data < root->data) {
        return search(root->left, data);
    }
    return search(root->right, data);
}

void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void preorder(Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

int main() {
    int i;
    Node* root = NULL;
    printf("Enter numbers to insert into the tree (end with -1):\n");
    do {
        scanf("%d", &i);
        if (i != -1) {
            root = insert(root, i);
        }
    } while (i != -1);

    printf("Enter search element: ");
    scanf("%d", &i);
    if (search(root, i)) {
        printf("Element %d found\n", i);
    } else {
        printf("Element %d not found\n", i);
    }

    printf("Inorder: ");
    inorder(root);
    printf("\nPreorder: ");
    preorder(root);
    printf("\nPostorder: ");
    postorder(root);

    return 0;
}
