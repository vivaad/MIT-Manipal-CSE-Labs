#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int m;
int n;

typedef struct Node {
    struct Node* link;
    int data;
} Node;

Node* table[50];  // Adjust the size of the table for the largest size.

Node* createNode(int key) {
    Node* new = (Node*)malloc(sizeof(Node));
    new->data = key;
    new->link = NULL;
    return new;
}

void hash(int hindex, int key) {
    Node* new_node = createNode(key);
    Node* current = table[hindex];
    if (!current) {
        table[hindex] = new_node;
        return;
    }
    while (current->link != NULL) {
        current = current->link;
    }
    current->link = new_node;
    return;
}

int hx(int key) {
    return key % m;  // Simple modulo hash function
}

void printHash() {
	for (int i = 0; i < m; i++) {		
        printf("Index %d: ", i);
        Node* temp = table[i];
        while (temp != NULL) {
            printf("%d ", temp->data);
            temp = temp->link;
        }
        printf("\n");
    }
}

int successfulSearch(int key) {
    int comparisons = 0;
    int hindex = hx(key);
    Node* current = table[hindex];
    while (current != NULL) {
        comparisons++;
        if (current->data == key) {
            return comparisons;  // Key found
        }
        current = current->link;
    }
    return comparisons;  // Key not found
}

int unsuccessfulSearch(int key) {
    int comparisons = 0;
    int hindex = hx(key);
    Node* current = table[hindex];
    while (current != NULL) {
        comparisons++;
        current = current->link;
    }
    return comparisons;  // Unsuccessful search
}

void work(int m_, int n_) {
    m = m_;
    n = n_;
    int a[n];
    printf("\n\nTesting with n = %d, m = %d (Load factor: %.2f)\n", n, m, (float)n / m);
    
    for (int i = 0; i < n; i++) {
        a[i] = rand() % 100;  // Generate random numbers between 0 and 99
    }

    // Initialize the hash table
    for (int i = 0; i < m; i++) {
        table[i] = NULL;
    }

    // Insert keys into the hash table
    for (int i = 0; i < n; i++) {
        int value = hx(a[i]);
        hash(value, a[i]);
    }

    // Print the hash table
    /* printHash(); */

    // Measure comparisons for successful search
    int successful_comparisons = 0;
    for (int i = 0; i < n; i++) {
        successful_comparisons += successfulSearch(a[i]);
    }
    printf("Total comparisons for successful searches: %d\n", successful_comparisons);

    // Measure comparisons for unsuccessful search (search for a non-existing key)
    int unsuccessful_comparisons = 0;
    for (int i = 0; i < n; i++) {
        int random_key = rand() % 100 + 100;  // Generate random keys that don't exist in the table
        unsuccessful_comparisons += unsuccessfulSearch(random_key);
    }
    printf("Total comparisons for unsuccessful searches: %d\n", unsuccessful_comparisons);
}

int main() {
    srand(time(NULL));

    int na[] = {50, 100, 200};  // Varying number of keys
    int ma[] = {10, 20, 50};    // Varying hash table sizes

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            work(ma[j], na[i]);
        }
    }

    return 0;
}

