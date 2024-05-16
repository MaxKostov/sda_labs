#include "lab7.h"

int main() {
    int choice;
    int o;
    int degree; // Degree for B+ tree
    BTreeNode* bTreeRoot = NULL;
    BPlusTreeNode* bPlusTreeRoot = NULL;
    AVLNode* avlTreeRoot = NULL;

    do {
        printf("\nChoose the data structure:\n");
        printf("1. B Tree\n");
        printf("2. B+ Tree\n");
        printf("3. AVL Tree\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // B Tree
            bTreeRoot = createBTree();
            do {
                printf("\nChoose the operation for B Tree:\n");
                printf("1. Insert\n");
                printf("2. Delete\n");
                printf("3. Search\n");
                printf("4. Traverse\n");
                printf("5. Register to File\n");
                printf("6. Back to Main Menu\n");
                printf("Enter operation choice: ");
                scanf("%d", &o);

                switch (o) {
                    case 1: {
                        TrainRegistration newEntry = get_train();
                        // You can similarly read other attributes
                        insertB(bTreeRoot, newEntry);
                        break;
                    }
                    case 2: {
                        int key;
                        printf("Enter train number to delete: ");
                        scanf("%d", &key);
                        deleteB(bTreeRoot, key);
                        break;
                    }
                    case 3: {
                        int key;
                        printf("Enter train number to search: ");
                        scanf("%d", &key);
                        if (searchB(bTreeRoot, key))
                            printf("Train found.\n");

                        else
                            printf("Train not found.\n");
                        break;
                    }
                    case 4:
                        printf("Traversing B Tree:\n");
                        traverseB(bTreeRoot);
                        printf("\n");
                        break;
                    case 5: {
                        char filename[100];
                        printf("Enter filename to register B Tree: ");
                        scanf("%s", filename);
                        registerBToFile(bTreeRoot, filename);
                        break;
                    }
                    case 6:
                        printf("Returning to main menu...\n");
                        break;
                    default:
                        printf("Invalid choice! Please enter a number between 1 and 6.\n");
                }

            } while (o != 6);
                break;
            case 2: // B+ Tree
                bPlusTreeRoot = createBPlusTree(3);
                do {
                        printf("\nChoose the operation for B+ Tree:\n");
                        printf("1. Insert\n");
                        printf("2. Delete\n");
                        printf("3. Search\n");
                        printf("4. Traverse\n");
                        printf("5. Register to File\n");
                        printf("6. Back to Main Menu\n");
                        printf("Enter operation choice: ");
                        scanf("%d", &o);

                        switch (o) {
                            case 1: {
                                TrainRegistration newEntry = get_train();
                                // You can similarly read other attributes
                                insertBPlus(bPlusTreeRoot, newEntry);
                                break;
                            }
                            case 2: {
                                int key;
                                printf("Enter train number to delete: ");
                                scanf("%d", &key);
                                deleteBPlus(bPlusTreeRoot, key);
                                break;
                            }
                            case 3: {
                                int key;
                                printf("Enter train number to search: ");
                                scanf("%d", &key);
                                if (searchBPlus(bPlusTreeRoot, key))
                                    printf("Train found.\n");
                                else
                                    printf("Train not found.\n");
                                break;
                            }
                            case 4:
                                printf("Traversing B+ Tree:\n");
                                traverseBPlus(bPlusTreeRoot);
                                printf("\n");
                                break;
                            case 5: {
                                char filename[100];
                                printf("Enter filename to register B+ Tree: ");
                                scanf("%s", filename);
                                registerBPlusToFile(bPlusTreeRoot, filename);
                                break;
                            }
                            case 6:
                                printf("Returning to main menu...\n");
                                break;
                            default:
                                printf("Invalid choice! Please enter a number between 1 and 6.\n");
                        }

                    } while (o != 6);
                break;
            case 3: // AVL Tree
                avlTreeRoot = createAVLTree();
                do {
                    printf("\nChoose the operation for AVL Tree:\n");
                    printf("1. Insert\n");
                    printf("2. Delete\n");
                    printf("3. Search\n");
                    printf("4. Traverse\n");
                    printf("5. Register to File\n");
                    printf("6. Back to Main Menu\n");
                    printf("Enter operation choice: ");
                    scanf("%d", &o);

                    switch (o) {
                        case 1: {
                            TrainRegistration newEntry = get_train();
                            avlTreeRoot = insertAVL(avlTreeRoot, newEntry);
                            break;
                        }
                        case 2: {
                            int key;
                            printf("Enter train number to delete: ");
                            scanf("%d", &key);
                            avlTreeRoot = deleteAVL(avlTreeRoot, key);
                            break;
                        }
                        case 3: {
                            int key;
                            printf("Enter train number to search: ");
                            scanf("%d", &key);
                            if (searchAVL(avlTreeRoot, key))
                                printf("Train found.\n");
                            else
                                printf("Train not found.\n");
                            break;
                        }
                        case 4:
                            printf("Traversing AVL Tree:\n");
                            traverseAVL(avlTreeRoot);
                            printf("\n");
                            break;
                        case 5: {
                            char filename[100];
                            printf("Enter filename to register AVL Tree: ");
                            scanf("%s", filename);
                            registerAVLToFile(avlTreeRoot, filename);
                            break;
                        }
                        case 6:
                            printf("Returning to main menu...\n");
                            break;
                        default:
                            printf("Invalid choice! Please enter a number between 1 and 6.\n");
                    }

                } while (o != 6);
                break;
            case 4: // Exit
                printf("Exiting the program...\n");
                break;
            default:
                printf("Invalid choice! Please enter a number between 1 and 4.\n");
        }

    } while (choice != 4);

    return 0;
}
