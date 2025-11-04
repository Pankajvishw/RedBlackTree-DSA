/***********************************************************************
 *  File Name   : main.c
 *  Description : Entry point for the Red-Black Tree Project.
 *                This file provides a menu-driven interface to perform
 *                basic Red-Black Tree operations including:
 *                  1. Node Insertion
 *                  2. Node Search
 *                  3. Node Deletion
 *                  4. Deleting Entire Tree
 *                  5. Inorder Traversal (Tree Visualization)
 *
 *                Functions:
 *                - main()             : Handles the main menu loop.
 *                - insert_node()      : Inserts a new node and maintains RB balance.
 *                - search_node()      : Searches for a specific node value.
 *                - delete_node()      : Removes a node and fixes tree balance.
 *                - delete_tree()      : Frees all allocated nodes.
 *                - print_tree()       : Displays the tree in a structured form.
 *
 *  Author      : Pankaj Kumar
 *  Roll No     : 25008_018
 *  Date        : 30-oct-2025
 ***********************************************************************/

#include "tree.h"

int main()
{
    Tree *root = NULL;    // Root pointer for the Red-Black Tree
    char choice;           // Menu option
    int data, flag;        // Data for node operations and status flag

    do 
    {
        printf("\n===========================================\n");
        printf("           RED-BLACK TREE PROJECT          \n");
        printf("===========================================\n");
        printf("1. Insert Node\n");
        printf("2. Search Node\n");
        printf("3. Remove Node\n");
        printf("4. Delete Entire Tree\n");
        printf("5. Display Tree\n");
        printf("6. Exit\n");
        printf("-------------------------------------------\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice)
        {
            case '1':
                printf("Enter the Data: ");
                scanf("%d", &data);
                flag = insert_node(&root, data);
                if (flag == SUCCESS)
                    printf("✅ Data %d inserted successfully.\n", data);
                else if (flag == DUPLICATE)
                    printf("⚠️  Duplicate Data %d not allowed.\n", data);
                else
                    printf("❌ Insertion failed.\n");
                break;

            case '2':
                printf("Enter the Data: ");
                scanf("%d", &data);
                flag = search_node(root, data);
                if (flag == SUCCESS)
                    printf("✅ Data %d found in the tree.\n", data);
                else
                    printf("❌ Data %d not found in the tree.\n", data);
                break;

            case '3':
                printf("Enter the Data: ");
                scanf("%d", &data);
                flag = delete_node(&root, data);
                if (flag == SUCCESS)
                    printf("✅ Data %d deleted successfully.\n", data);
                else
                    printf("❌ Data %d not found in the tree.\n", data);
                break;

            case '4':
                if (delete_tree(&root) == SUCCESS)
                    printf("🗑️  Tree deleted successfully.\n");
                else
                    printf("❌ Tree is already empty.\n");
                break;

            case '5':
                printf("\nTree Structure (Inorder View):\n");
                print_tree(root, 0);
                break;

            case '6':
                printf("👋 Exiting Red-Black Tree Program...\n");
                break;

            default:
                printf("⚠️  Invalid choice! Please try again.\n");
                break;
        }

    } while (choice != '6');

    free(root);  // Final cleanup before exit
    return 0;
}
