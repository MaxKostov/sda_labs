#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_KEYS 100
#define MAX_CHILDREN MAX_KEYS + 1


// Define your custom data type structures here
typedef enum week { Mon = 1, Tue, Wed, Thur, Fri, Sat, Sun } Week;

typedef struct train_reg {
    int number;
    char destination[100];
    int departure_hour;
    int departure_min;
    int arrival_hour;
    int arrival_min;
    Week day;
} TrainRegistration;

typedef struct AVLNode {
    TrainRegistration data;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
} AVLNode;

// Function to create an AVL tree
AVLNode* createAVLTree() {
    return NULL;
}

// Function to get height of a node
int height(AVLNode* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

void display_train(TrainRegistration train) {
    printf("Train number: %d\n", train.number);
    printf("Destination: %s\n", train.destination);
    printf("Day: %d\n", train.day);
    printf("Departure time: %02d:%02d\n", train.departure_hour, train.departure_min);
    printf("Arrival time: %02d:%02d\n", train.arrival_hour, train.arrival_min);
    printf("\n");
}

// Function to get maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to right rotate subtree rooted with y
AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

// Function to left rotate subtree rooted with x
AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

// Get Balance factor of node N
int getBalance(AVLNode* node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Function to insert a node in AVL tree
AVLNode* insertAVL(AVLNode* node, TrainRegistration data) {
    // Perform the normal BST rotation
    if (node == NULL) {
        AVLNode* newNode = (AVLNode*)malloc(sizeof(AVLNode));
        newNode->data = data;
        newNode->left = newNode->right = NULL;
        newNode->height = 1;
        return newNode;
    }

    if (data.number < node->data.number)
        node->left = insertAVL(node->left, data);
    else if (data.number > node->data.number)
        node->right = insertAVL(node->right, data);
    else // Equal keys are not allowed in BST
        return node;

    // Update height of this ancestor node
    node->height = 1 + max(height(node->left), height(node->right));

    // Get the balance factor of this ancestor node to check whether this node became unbalanced
    int balance = getBalance(node);

    // If this node becomes unbalanced, then there are four cases

    // Left Left Case
    if (balance > 1 && data.number < node->left->data.number)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && data.number > node->right->data.number)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && data.number > node->left->data.number) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && data.number < node->right->data.number) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Return the (unchanged) node pointer
    return node;
}

AVLNode* deleteAVL(AVLNode* root, int key) {
    // Step 1: Perform standard binary search tree deletion
    if (root == NULL)
        return root;

    if (key < root->data.number)
        root->left = deleteAVL(root->left, key);
    else if (key > root->data.number)
        root->right = deleteAVL(root->right, key);
    else {
        // Node with only one child or no child
        if (root->left == NULL || root->right == NULL) {
            AVLNode* temp = root->left ? root->left : root->right;

            // No child case
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else // One child case
                *root = *temp; // Copy the contents of the non-empty child

            free(temp);
        } else {
            // Node with two children: Get the inorder successor (smallest in the right subtree)
            AVLNode* temp = minValueNode(root->right);

            // Copy the inorder successor's data to this node
            root->data = temp->data;

            // Delete the inorder successor
            root->right = deleteAVL(root->right, temp->data.number);
        }
    }

    // If the tree had only one node then return
    if (root == NULL)
        return root;

    // Step 2: Update the height of the current node
    root->height = 1 + (height(root->left) > height(root->right) ? height(root->left) : height(root->right));

    // Step 3: Get the balance factor of this node to check whether it became unbalanced
    int balance = height(root->left) - height(root->right);

    // If this node becomes unbalanced, then there are four cases

    // Left Left case
    if (balance > 1 && height(root->left->left) >= height(root->left->right))
        return rightRotate(root);

    // Left Right case
    if (balance > 1 && height(root->left->left) < height(root->left->right)) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right case
    if (balance < -1 && height(root->right->right) >= height(root->right->left))
        return leftRotate(root);

    // Right Left case
    if (balance < -1 && height(root->right->right) < height(root->right->left)) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function to search for a node in AVL tree
AVLNode* searchAVL(AVLNode* root, int key) {
    if (root == NULL || root->data.number == key)
        return root;

    if (root->data.number < key)
        return searchAVL(root->right, key);

    return searchAVL(root->left, key);
}

// Function to traverse AVL tree (inorder)
void traverseAVLUtil(AVLNode* root) {
    if (root == NULL)
        return;
    traverseAVLUtil(root->left);
    printf("Train Number: %d\n", root->data.number);
    printf("Destination: %s\n", root->data.destination);
    printf("Departure Time: %02d:%02d\n", root->data.departure_hour, root->data.departure_min);
    printf("Arrival Time: %02d:%02d\n", root->data.arrival_hour, root->data.arrival_min);
    printf("Day: %d\n", root->data.day);
    printf("\n");
    traverseAVLUtil(root->right);
}

void traverseAVL(AVLNode* root) {
    traverseAVLUtil(root);
}

// Function to register AVL tree data to a file
void registerAVLToFileUtil(AVLNode* root, FILE* file) {
    if (root == NULL)
        return;
    registerAVLToFileUtil(root->left, file);
    fprintf(file, "%d %s %d:%d, %d:%d, %d\n", root->data.number, root->data.destination, root->data.departure_hour, root->data.departure_min, root->data.arrival_hour, root->data.arrival_min, root->data.day);
    registerAVLToFileUtil(root->right, file);
}

void registerAVLToFile(AVLNode* root, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    registerAVLToFileUtil(root, file);
    fclose(file);
}

typedef struct BTreeNode {
    TrainRegistration *keys;
    struct BTreeNode **child;
    bool leaf;
    int n; // Number of keys currently stored in the node
} BTreeNode;

BTreeNode* createBTree() {
    BTreeNode* root = (BTreeNode*)malloc(sizeof(BTreeNode));
    root->keys = (TrainRegistration*)malloc(sizeof(TrainRegistration) * MAX_KEYS);
    root->child = (BTreeNode**)malloc(sizeof(BTreeNode*) * MAX_CHILDREN);
    root->leaf = true;
    root->n = 0;
    return root;
}

// Function to search for a node in B tree
BTreeNode* searchB(BTreeNode* root, int key) {
    int i = 0;
    while (i < root->n && key > root->keys[i].number)
        i++;

    if (i < root->n && key == root->keys[i].number)
        return root;

    if (root->leaf)
        return NULL;

    return searchB(root->child[i], key);
}

// Function to insert a node in B tree
void insertB(BTreeNode* root, TrainRegistration data) {
    if (root->n == MAX_KEYS) {
        // Split the root
        BTreeNode* new_root = createBTree();
        new_root->leaf = false;
        new_root->child[0] = root;

        // Split child
        BTreeNode* new_child = createBTree();
        new_child->leaf = root->leaf;
        new_child->n = MAX_KEYS / 2;

        root->n = MAX_KEYS / 2 + 1;

        // Copy keys and children to the new child
        for (int i = 0; i < MAX_KEYS / 2; i++) {
            new_child->keys[i] = root->keys[i + root->n];
            new_child->child[i] = root->child[i + root->n];
        }
        new_child->child[MAX_KEYS / 2] = root->child[MAX_KEYS];

        // Update the root
        new_root->keys[0] = root->keys[root->n - 1];
        new_root->child[1] = new_child;
        new_root->n = 1;
        root = new_root;
    }

    int i = root->n - 1;
    if (root->leaf) {
        while (i >= 0 && data.number < root->keys[i].number) {
            root->keys[i + 1] = root->keys[i];
            i--;
        }
        root->keys[i + 1] = data;
        root->n++;
    } else {
        while (i >= 0 && data.number < root->keys[i].number)
            i--;
        i++;
        if (root->child[i]->n == MAX_KEYS) {
            // Split child
            BTreeNode* new_child = createBTree();
            new_child->leaf = root->child[i]->leaf;
            new_child->n = MAX_KEYS / 2;

            root->child[i]->n = MAX_KEYS / 2;

            // Copy keys and children to the new child
            for (int j = 0; j < MAX_KEYS / 2; j++) {
                new_child->keys[j] = root->child[i]->keys[j + root->child[i]->n];
                new_child->child[j] = root->child[i]->child[j + root->child[i]->n];
            }
            new_child->child[MAX_KEYS / 2] = root->child[i]->child[MAX_KEYS];

            // Update the root
            for (int j = root->n; j > i; j--) {
                root->child[j + 1] = root->child[j];
            }
            root->child[i + 1] = new_child;
            root->keys[i] = root->child[i]->keys[root->child[i]->n - 1];
            root->n++;
            if (data.number > root->keys[i].number)
                i++;
        }
        insertB(root->child[i], data);
    }
}

// Function to search for the node containing the key to be deleted
BTreeNode* searchKey(BTreeNode* root, int key) {
    int i = 0;
    while (i < root->n && key > root->keys[i].number)
        i++;
    if (i < root->n && key == root->keys[i].number)
        return root;
    if (root->leaf)
        return NULL;
    return searchKey(root->child[i], key);
}

// Function to find the predecessor of a given key in a B tree node
int findPredecessor(BTreeNode* root, int idx) {
    BTreeNode* curr = root->child[idx];
    while (!curr->leaf)
        curr = curr->child[curr->n];
    return curr->keys[curr->n - 1].number;
}

// Function to find the successor of a given key in a B tree node
int findSuccessor(BTreeNode* root, int idx) {
    BTreeNode* curr = root->child[idx + 1];
    while (!curr->leaf)
        curr = curr->child[0];
    return curr->keys[0].number;
}

// Function to delete a node in B tree
void deleteB(BTreeNode* root, int key) {
    if (!root)
        return;

    // Step 1: Search for the node containing the key to be deleted
    int idx = 0;
    while (idx < root->n && key > root->keys[idx].number)
        idx++;

    // If the key is present in an internal node
    if (idx < root->n && key == root->keys[idx].number) {
        if (root->leaf) {
            // If the key is present in a leaf node, simply delete it
            for (int i = idx + 1; i < root->n; i++)
                root->keys[i - 1] = root->keys[i];
            root->n--;
        } else {
            // If the key is present in an internal node, find its successor/predecessor and replace the key with it
            int pred = findPredecessor(root, idx);
            root->keys[idx].number = pred;
            deleteB(root->child[idx], pred);
        }
    } else {
        // If the key is not present in the current node
        if (root->leaf) {
            // Key not found in the tree
            return;
        }
        bool flag = (idx == root->n);

        // Check if the child where the key could be is underflowed
        if (root->child[idx]->n < 2) {
            // Attempt to borrow a key from the left sibling
            if (idx != 0 && root->child[idx - 1]->n >= 2) {
                // Transfer a key from the left sibling to the current node
                root->child[idx]->keys[0] = root->keys[idx - 1];
                root->keys[idx - 1] = root->child[idx - 1]->keys[root->child[idx - 1]->n - 1];
                root->child[idx]->n++;
                root->child[idx - 1]->n--;
            }
            // Attempt to borrow a key from the right sibling
            else if (idx != root->n && root->child[idx + 1]->n >= 2) {
                // Transfer a key from the right sibling to the current node
                root->child[idx]->keys[0] = root->keys[idx];
                root->keys[idx] = root->child[idx + 1]->keys[0];
                for (int i = 0; i < root->child[idx + 1]->n - 1; i++)
                    root->child[idx + 1]->keys[i] = root->child[idx + 1]->keys[i + 1];
                root->child[idx]->n++;
                root->child[idx + 1]->n--;
            }
            // Merge the child with one of its siblings
            else {
                if (idx != root->n) {
                    // Merge with the right sibling
                    root->child[idx]->keys[0] = root->keys[idx];
                    for (int i = 0; i < root->child[idx + 1]->n; i++)
                        root->child[idx]->keys[i + 1] = root->child[idx + 1]->keys[i];
                    root->child[idx]->n = root->child[idx + 1]->n + 1;
                    for (int i = idx + 1; i < root->n; i++) {
                        root->keys[i - 1] = root->keys[i];
                        root->child[i] = root->child[i + 1];
                    }
                    root->n--;
                } else {
                    // Merge with the left sibling
                    idx--;
                    root->child[idx]->keys[root->child[idx]->n] = root->keys[idx];
                    for (int i = 0; i < root->child[idx + 1]->n; i++)
                        root->child[idx]->keys[root->child[idx]->n + 1 + i] = root->child[idx + 1]->keys[i];
                    root->child[idx]->n = root->child[idx + 1]->n + 1;
                    for (int i = idx + 1; i < root->n; i++) {
                        root->keys[i - 1] = root->keys[i];
                        root->child[i] = root->child[i + 1];
                    }
                    root->n--;
                }
            }
        }

        // Recursively delete the key from the appropriate child
        deleteB(root->child[idx], key);
    }

    // Step 5: If the root becomes empty after deletion, update the root pointer
    if (root->n == 0 && root != NULL) {
        if (root->leaf)
            root = NULL;
        else
            root = root->child[0];
    }
}

// Function to traverse B tree (inorder)
void traverseBUtil(BTreeNode* root) {
    if (root != NULL) {
        int i;
        for (i = 0; i < root->n; i++) {
            if (!root->leaf)
                traverseBUtil(root->child[i]);
            //printf("%d ", root->keys[i].number);
            display_train(*root->keys);

        }
        if (!root->leaf)
            traverseBUtil(root->child[i]);
    }
}

void traverseB(BTreeNode* root) {
    traverseBUtil(root);
}

// Function to register B tree data to a file
void registerBToFileUtil(BTreeNode* root, FILE* file) {
    if (root != NULL) {
        int i;
        for (i = 0; i < root->n; i++) {
            if (!root->leaf)
                registerBToFileUtil(root->child[i], file);
            fprintf(file, "%d, %s, %d, %d:%d, %d:%d", root->keys[i].number, root->keys[i].destination, root->keys[i].day, root->keys[i].departure_hour, root->keys[i].arrival_min, root->keys[i].arrival_hour, root->keys[i].arrival_min);
        }
        if (!root->leaf)
            registerBToFileUtil(root->child[i], file);
    }
}

void registerBToFile(BTreeNode* root, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    registerBToFileUtil(root, file);
    fclose(file);
}

typedef struct BPlusTreeNode {
    TrainRegistration *keys;
    struct BPlusTreeNode **pointers;
    struct BPlusTreeNode *next;
    int numKeys;
    bool isLeaf;
} BPlusTreeNode;

BPlusTreeNode* createBPlusTreeNode(int degree) {
    BPlusTreeNode* node = (BPlusTreeNode*)malloc(sizeof(BPlusTreeNode));
    node->keys = (TrainRegistration*)malloc(sizeof(TrainRegistration) * degree);
    node->pointers = (BPlusTreeNode**)malloc(sizeof(BPlusTreeNode*) * (degree + 1));
    node->next = NULL;
    node->numKeys = 0;
    node->isLeaf = true;
    return node;
}

BPlusTreeNode* createBPlusTree(int degree) {
    return createBPlusTreeNode(degree);
}

void insertBPlus(BPlusTreeNode* root, TrainRegistration data) {
    // If the root is a leaf node
    if (root->isLeaf) {
        int i = root->numKeys - 1;
        // Find the position to insert the new key
        while (i >= 0 && data.number < root->keys[i].number) {
            root->keys[i + 1] = root->keys[i];
            i--;
        }
        // Insert the new key
        root->keys[i + 1] = data;
        root->numKeys++;
    } else {
        // Find the child to insert the new key
        int i = root->numKeys - 1;
        while (i >= 0 && data.number < root->keys[i].number)
            i--;

        i++;

        // Check if the child is full
        if (root->pointers[i]->numKeys == 2 * root->numKeys) {
            // Split the child
            BPlusTreeNode* newChild = createBPlusTreeNode(root->numKeys);
            newChild->isLeaf = root->pointers[i]->isLeaf;
            newChild->next = root->pointers[i]->next;
            root->pointers[i]->next = newChild;

            // Move the keys and pointers to the new child
            for (int j = 0; j < root->numKeys; j++) {
                newChild->keys[j] = root->pointers[i]->keys[j + root->numKeys];
                newChild->pointers[j] = root->pointers[i]->pointers[j + root->numKeys];
            }
            newChild->pointers[root->numKeys] = root->pointers[i]->pointers[2 * root->numKeys];

            // Update the number of keys in the child
            newChild->numKeys = root->numKeys;

            // Update the parent node
            for (int j = root->numKeys - 1; j >= i; j--) {
                root->keys[j + 1] = root->keys[j];
                root->pointers[j + 2] = root->pointers[j + 1];
            }
            root->keys[i - 1] = newChild->keys[0];
            root->pointers[i] = newChild;

            // Recursive insertion
            if (data.number > root->keys[i - 1].number)
                i++;
        }
        insertBPlus(root->pointers[i], data);
    }
}


void traverseBPlusUtil(BPlusTreeNode* root) {
    if (root != NULL) {
        if (root->isLeaf) {
            for (int i = 0; i < root->numKeys; i++) {
                //printf("%d ", root->keys[i].number);
                display_train(*root->keys);
            }
        } else {
            for (int i = 0; i < root->numKeys; i++) {
                traverseBPlusUtil(root->pointers[i]);
                //printf("%d ", root->keys[i].number);
                display_train(*root->keys);
            }
            traverseBPlusUtil(root->pointers[root->numKeys]);
        }
    }
}

void traverseBPlus(BPlusTreeNode* root) {
    traverseBPlusUtil(root);
}

void registerBPlusToFileUtil(BPlusTreeNode* root, FILE* file) {
    if (root != NULL) {
        if (root->isLeaf) {
            for (int i = 0; i < root->numKeys; i++) {
                fprintf(file, "%d, %s, %d, %d:%d, %d:%d", root->keys[i].number, root->keys[i].destination, root->keys[i].day, root->keys[i].departure_hour, root->keys[i].arrival_min, root->keys[i].arrival_hour, root->keys[i].arrival_min);
            }
        } else {
            for (int i = 0; i < root->numKeys; i++) {
                registerBPlusToFileUtil(root->pointers[i], file);
                fprintf(file, "%d, %s, %d, %d:%d, %d:%d", root->keys[i].number, root->keys[i].destination, root->keys[i].day, root->keys[i].departure_hour, root->keys[i].arrival_min, root->keys[i].arrival_hour, root->keys[i].arrival_min);
            }
            registerBPlusToFileUtil(root->pointers[root->numKeys], file);
        }
    }
}

void registerBPlusToFile(BPlusTreeNode* root, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    registerBPlusToFileUtil(root, file);
    fclose(file);
}

BPlusTreeNode* searchBPlus(BPlusTreeNode* root, int key) {
    if (root == NULL) // If the root is NULL, the tree is empty
        return NULL;

    // Find the index of the smallest key greater than or equal to the search key
    int i = 0;
    while (i < root->numKeys && key > root->keys[i].number)
        i++;

    // If the key is found at this node, return the node
    if (i < root->numKeys && key == root->keys[i].number)
        return root;

    // If this is a leaf node, the key does not exist in the tree
    if (root->isLeaf)
        return NULL;

    // Recursively search in the appropriate child node
    return searchBPlus(root->pointers[i], key);
}

void deleteBPlus(BPlusTreeNode* root, int key) {
    // If the root is NULL, the tree is empty
    if (root == NULL)
        return;

    // Find the index of the smallest key greater than or equal to the search key
    int i = 0;
    while (i < root->numKeys && key > root->keys[i].number)
        i++;

    // If the key is found at this node
    if (i < root->numKeys && key == root->keys[i].number) {
        // If this is a leaf node, simply remove the key
        if (root->isLeaf) {
            for (int j = i; j < root->numKeys - 1; j++) {
                root->keys[j] = root->keys[j + 1];
            }
            root->numKeys--;
        } else {
            // If this is an internal node, replace the key with the smallest key from its right subtree
            BPlusTreeNode* successor = root->pointers[i + 1];
            while (!successor->isLeaf)
                successor = successor->pointers[0];
            
            root->keys[i] = successor->keys[0];
            deleteBPlus(successor, successor->keys[0].number);
        }
    } else {
        // If the key is not found at this node, recursively delete it from the appropriate child node
        deleteBPlus(root->pointers[i], key);
    }
}

// Function implementations
TrainRegistration get_train() {
    TrainRegistration train;
    char *destination = malloc(100 * sizeof(char));
    enum week day;
    printf("Enter the number of the train: ");
    scanf("%d", &train.number);

    printf("Enter the destination: ");
    scanf("%s", destination);
    strcpy(train.destination, destination);
    
    
    char input[4];

    printf("Enter the day of the week (Mon, Tue, ..., Sun): ");
    scanf("%s", input);
    for (int i = 0; input[i]; i++) {
    input[i] = tolower(input[i]);
    }

    if (strcmp(input, "mon") == 0) {
        day = Mon;
    } else if (strcmp(input, "tue") == 0) {
        day = Tue;
    } else if (strcmp(input, "wed") == 0) {
        day = Wed;
    } else if (strcmp(input, "thur") == 0) {
        day = Thur;
    } else if (strcmp(input, "fri") == 0) {
        day = Fri;
    } else if (strcmp(input, "sat") == 0) {
        day = Sat;
    } else if (strcmp(input, "sun") == 0) {
        day = Sun;
    } else {
        printf("Invalid input\n");
    }

    train.day = day;

    printf("Enter the departure time (hours:minutes)");
    scanf("%d:%d", &train.departure_hour, &train.departure_min);
    printf("Enter the arrival time (hours:minutes)");
    scanf("%d:%d", &train.arrival_hour, &train.arrival_min);

    return train;
}