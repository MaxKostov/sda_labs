#ifndef LAB7_H
#define LAB7_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

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

// Define AVL Tree node
typedef struct AVLNode {
    TrainRegistration data;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
} AVLNode;

typedef struct BTreeNode {
    TrainRegistration *keys;
    struct BTreeNode **child;
    bool leaf;
    int n; // Number of keys currently stored in the node
} BTreeNode;

// Define B+ Tree node
typedef struct BPlusTreeNode {
    TrainRegistration *keys;
    struct BPlusTreeNode **pointers;
    struct BPlusTreeNode *next;
    int numKeys;
    bool isLeaf;
} BPlusTreeNode;


// AVL Tree functions
AVLNode* createAVLTree();
AVLNode* insertAVL(AVLNode* root, TrainRegistration data);
AVLNode* deleteAVL(AVLNode* root, int key);
AVLNode* searchAVL(AVLNode* root, int key);
void traverseAVL(AVLNode* root);
void registerAVLToFile(AVLNode* root, const char* filename);

// B Tree functions
BTreeNode* createBTree();
void insertB(BTreeNode* root, TrainRegistration data);
void deleteB(BTreeNode* root, int key);
BTreeNode* searchB(BTreeNode* root, int key);
void traverseB(BTreeNode* root);
void registerBToFile(BTreeNode* root, const char* filename);

// B+ Tree functions
BPlusTreeNode* createBPlusTree(int degree);
void insertBPlus(BPlusTreeNode* root, TrainRegistration data);
void deleteBPlus(BPlusTreeNode* root, int key);
BPlusTreeNode* searchBPlus(BPlusTreeNode* root, int key);
void traverseBPlus(BPlusTreeNode* root);
void registerBPlusToFile(BPlusTreeNode* root, const char* filename);


TrainRegistration get_train();
void display_train(TrainRegistration train);

#endif