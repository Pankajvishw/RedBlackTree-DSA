/***********************************************************************
 *  File Name   : tree.c
 *  Description : This file implements all core functionalities of the
 *                Red-Black Tree (RBT) data structure including:
 *                  - Node creation
 *                  - Left and right rotations
 *                  - Insertion with balancing
 *                  - Deletion with double-black fixup
 *                  - Tree traversal and visualization
 *                  - Tree search and full deletion
 *
 *                The Red-Black Tree ensures balanced height for efficient
 *                operations with O(log n) complexity for insertion,
 *                deletion, and search.
 *
 *  Functions:
 *      - right_rotate()
 *      - left_rotate()
 *      - create_node()
 *      - insert_node()
 *      - findmin()
 *      - getsibling_node()
 *      - is_left_child()
 *      - fix_double_black()
 *      - delete_node()
 *      - search_node()
 *      - delete_tree()
 *      - print_color()
 *      - print_tree()
 *
 *  Author      : Pankaj Kumar
 *  Roll No     : 25008_018
 *  Date        : 14-Sep-2025
 ***********************************************************************/

#include "tree.h"

/* --------------------------------------------------------------------
 * Function: right_rotate()
 * Description: Performs a right rotation on a given node.
 * --------------------------------------------------------------------*/
void right_rotate(Tree **root, Tree *node)
{
    Tree *temp = node->left;
    node->left = temp->right;
    if (temp->right != NULL)
        temp->right->parent = node;

    temp->parent = node->parent;
    
    if (node->parent == NULL)
        *root = temp;
    else if (node == node->parent->right)
        node->parent->right = temp;
    else
        node->parent->left = temp;
    
    temp->right = node;
    node->parent = temp;
}

/* --------------------------------------------------------------------
 * Function: left_rotate()
 * Description: Performs a left rotation on a given node.
 * --------------------------------------------------------------------*/
void left_rotate(Tree **root, Tree *node)
{
    Tree *temp = node->right;
    node->right = temp->left;
    if (temp->left != NULL)
        temp->left->parent = node;

    temp->parent = node->parent;
    
    if (node->parent == NULL)
        *root = temp;
    else if (node == node->parent->left)
        node->parent->left = temp;
    else
        node->parent->right = temp;
    
    temp->left = node;
    node->parent = temp;
}

/* --------------------------------------------------------------------
 * Function: create_node()
 * Description: Allocates and initializes a new Red-Black Tree node.
 * --------------------------------------------------------------------*/
Tree *create_node(int data)
{
    Tree *newNode = malloc(sizeof(Tree));
    if (newNode == NULL)
        return NULL;

    newNode->data = data;
    newNode->parent = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->color = RED;   // New nodes are always red initially
    return newNode;
}

/* --------------------------------------------------------------------
 * Function: insert_node()
 * Description: Inserts a node into the Red-Black Tree and fixes
 *              any property violations using rotations and color flips.
 * --------------------------------------------------------------------*/
int insert_node(Tree **root, int data)
{
    Tree *temp = *root, *prev = NULL;

    // Standard BST insertion
    while (temp)
    {
        prev = temp;
        if (data < temp->data)
            temp = temp->left;
        else if (data > temp->data)
            temp = temp->right;
        else
            return DUPLICATE;  // Duplicate not allowed
    }

    Tree *newNode = create_node(data);
    if (newNode == NULL)
        return FAILURE;

    if (*root == NULL)
    {
        newNode->color = BLACK;
        *root = newNode;
        return SUCCESS;
    }

    newNode->parent = prev;
    if (data < prev->data)
        prev->left = newNode;
    else
        prev->right = newNode;

    // Fix Red-Black Tree violations
    Tree *node = newNode, *uncle;
    while (node != *root && node->parent->color == RED)
    {
        if (node->parent == node->parent->parent->left)
        {
            uncle = node->parent->parent->right;
            if (uncle && uncle->color == RED)
            {
                // Case 1: Recoloring
                uncle->color = BLACK;
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            }
            else
            {
                // Case 2/3: Rotation
                if (node == node->parent->right)
                {
                    node = node->parent;
                    left_rotate(root, node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                right_rotate(root, node->parent->parent);
            }
        }
        else
        {
            uncle = node->parent->parent->left;
            if (uncle && uncle->color == RED)
            {
                uncle->color = BLACK;
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            }
            else
            {
                if (node == node->parent->left)
                {
                    node = node->parent;
                    right_rotate(root, node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                left_rotate(root, node->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;
    return SUCCESS;
}

/* --------------------------------------------------------------------
 * Helper Function: findmin()
 * Description: Returns the leftmost node (smallest value) in a subtree.
 * --------------------------------------------------------------------*/
Tree *findmin(Tree *root)
{
    while (root && root->left)
        root = root->left;
    return root;
}

/* --------------------------------------------------------------------
 * Helper Function: getsibling_node()
 * Description: Returns the sibling of a given node.
 * --------------------------------------------------------------------*/
Tree *getsibling_node(Tree *node)
{
    if (node->parent == NULL)
        return NULL;
    return (node == node->parent->left)
                ? node->parent->right
                : node->parent->left;
}

/* --------------------------------------------------------------------
 * Helper Function: is_left_child()
 * Description: Checks if a node is a left child of its parent.
 * --------------------------------------------------------------------*/
int is_left_child(Tree *node)
{
    return (node->parent && node == node->parent->left);
}

/* --------------------------------------------------------------------
 * Function: fix_double_black()
 * Description: Fixes Red-Black property violations caused by
 *              deleting a black node.
 * --------------------------------------------------------------------*/
void fix_double_black(Tree **root, Tree *node)
{
    if (node == *root)
        return;

    Tree *sibling = getsibling_node(node);

    if (sibling == NULL)
    {
        fix_double_black(root, node->parent);
    }
    else
    {
        if (sibling->color == RED)
        {
            node->parent->color = RED;
            sibling->color = BLACK;
            if (is_left_child(sibling))
                right_rotate(root, node->parent);
            else
                left_rotate(root, node->parent);
            fix_double_black(root, node);
        }
        else
        {
            if ((sibling->left && sibling->left->color == RED) ||
                (sibling->right && sibling->right->color == RED))
            {
                if (sibling->left && sibling->left->color == RED)
                {
                    if (is_left_child(sibling))
                    {
                        sibling->left->color = sibling->color;
                        sibling->color = node->parent->color;
                        right_rotate(root, node->parent);
                    }
                    else
                    {
                        sibling->left->color = node->parent->color;
                        right_rotate(root, sibling);
                        left_rotate(root, node->parent);
                    }
                }
                else
                {
                    if (is_left_child(sibling))
                    {
                        sibling->right->color = node->parent->color;
                        left_rotate(root, sibling);
                        right_rotate(root, node->parent);
                    }
                    else
                    {
                        sibling->right->color = sibling->color;
                        sibling->color = node->parent->color;
                        left_rotate(root, node->parent);
                    }
                }
                node->parent->color = BLACK;
            }
            else
            {
                sibling->color = RED;
                if (node->parent->color == BLACK)
                    fix_double_black(root, node->parent);
                else
                    node->parent->color = BLACK;
            }
        }
    }
}

/* --------------------------------------------------------------------
 * Function: delete_node()
 * Description: Deletes a node by value from the tree and ensures
 *              Red-Black balance is restored.
 * --------------------------------------------------------------------*/
int delete_node(Tree **root, int data)
{
    if (*root == NULL)
        return FAILURE;

    Tree *temp = *root;
    while (temp)
    {
        if (temp->data == data)
            break;
        else if (data < temp->data)
            temp = temp->left;
        else
            temp = temp->right;
    }

    if (temp == NULL)
        return DATA_NOT_FOUND;

    Tree *to_delete = temp;
    if (temp->left && temp->right)
    {
        Tree *succ = findmin(temp->right);
        temp->data = succ->data;
        to_delete = succ;
    }

    Tree *child = (to_delete->left) ? to_delete->left : to_delete->right;
    int db = ((child == NULL || child->color == BLACK) && to_delete->color == BLACK);

    if (child)
        child->parent = to_delete->parent;

    if (to_delete->parent == NULL)
        *root = child;
    else if (is_left_child(to_delete))
        to_delete->parent->left = child;
    else
        to_delete->parent->right = child;

    if (db)
    {
        if (child)
            fix_double_black(root, child);
        else
            fix_double_black(root, to_delete);
    }
    else if (child)
        child->color = BLACK;

    free(to_delete);
    return SUCCESS;
}

/* --------------------------------------------------------------------
 * Function: search_node()
 * Description: Searches for a node by value.
 * --------------------------------------------------------------------*/
int search_node(Tree *root, int data)
{
    while (root)
    {
        if (root->data == data)
            return SUCCESS;
        root = (data < root->data) ? root->left : root->right;
    }
    return DATA_NOT_FOUND;
}

/* --------------------------------------------------------------------
 * Function: delete_tree()
 * Description: Recursively frees all nodes in the tree.
 * --------------------------------------------------------------------*/
int delete_tree(Tree **root)
{
    if (*root == NULL)
        return SUCCESS;

    delete_tree(&((*root)->left));
    delete_tree(&((*root)->right));
    free(*root);
    *root = NULL;
    return SUCCESS;
}

/* --------------------------------------------------------------------
 * Function: print_color()
 * Description: Prints node color as RED or BLACK.
 * --------------------------------------------------------------------*/
void print_color(int color)
{
    if (color == RED)
        printf("\033[1;31mRED\033[0m");   // bright red
    else
        printf("\033[1;30mBLACK\033[0m"); // bright black (gray)
}

/* --------------------------------------------------------------------
 * Function: print_tree()
 * Description: Recursively prints tree in a pretty format showing
 *              hierarchy and colors.
 * --------------------------------------------------------------------*/
void print_tree(Tree *root, int space)
{
    if (root == NULL)
        return;

    space += SPACE_STEP;
    print_tree(root->right, space);

    printf("\n");
    PRINT_SPACES(space);
    printf("%d(", root->data);
    print_color(root->color);
    printf(")\n");

    print_tree(root->left, space);
}
