#include <stdio.h>
#include <stdlib.h>

struct Node {
    struct Node *left, *right;
    int key;
};


struct Node* lca(struct Node* root, int n1, int n2) {
  
    if (root == NULL)
        return NULL;

    // If either key matches with root data, return root
    if (root->key == n1 || root->key == n2)
        return root;

    // Look for keys in left and right subtrees
    struct Node* leftLca = lca(root->left, n1, n2);
    struct Node* rightLca = lca(root->right, n1, n2);

    // If both of the above calls return Non-NULL, then one
    // key is present in once subtree and other is present
    // in other, So this node is the LCA
    if (leftLca && rightLca)
        return root;

    // Otherwise check if left subtree or right subtree is
    // LCA
    return (leftLca != NULL) ? leftLca : rightLca;
}

struct Node* createnode(int key) {
    struct Node* newnode = 
          (struct Node*)malloc(sizeof(struct Node));
    newnode->key = key;
    newnode->left = newnode->right = NULL;
    return newnode;
}

int main() {

    struct Node* root = createnode(20);
    root->left = createnode(8);
    root->right = createnode(22);
    root->left->left = createnode(4);
    root->left->right = createnode(12);
    root->left->right->left = createnode(10);
    root->left->right->right = createnode(14);
    
    printf("Enter numbers:");
    int a, b;
    scanf("%d %d", &a, &b);

    struct Node* ans = lca(root, a, b);
    if(ans == NULL){
        printf("No common ancestor found");
    }
    else{
        printf("%d", ans->key);
    }
    return 0;
}
