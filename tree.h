/***********************************************************************
 *  File Name   : tree.h
 *  Description : Header file for the Red-Black Tree Project.
 *                Contains macro definitions, structure declarations,
 *                and function prototypes for all tree operations.
 *
 *                This file defines:
 *                - Node structure for Red-Black Tree
 *                - Color macros (RED / BLACK)
 *                - Function prototypes for insertion, deletion, search,
 *                  rotations, balancing, and tree display.
 *
 *  Functions:
 *                - left_rotate() / right_rotate() : Tree rotations
 *                - create_node()                  : Node creation
 *                - insert_node()                  : Insert new data
 *                - delete_node()                  : Delete a specific node
 *                - delete_tree()                  : Free the entire tree
 *                - fix_double_black()             : Balance tree after deletion
 *                - search_node()                  : Search for a data value
 *                - getsibling_node()              : Get sibling of a node
 *                - print_color() / print_tree()   : Display helpers
 *
 *  Author      : Pankaj Kumar
 *  Roll No     : 25008_018
 *  Date        : 30-oct-2025
 ***********************************************************************/

#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>

/*--------------------------------------------------------------
 *                      STATUS MACROS
 *-------------------------------------------------------------*/
#define SUCCESS 0
#define FAILURE -1
#define DUPLICATE -2
#define LIST_EMPTY -3
#define DATA_NOT_FOUND -4

/*--------------------------------------------------------------
 *                      DISPLAY MACROS
 *-------------------------------------------------------------*/
#define SPACE_STEP 10          // number of spaces between tree levels
#define PRINT_SPACES(n) for (int i = 0; i < n; i++) printf(" ");

/*--------------------------------------------------------------
 *                      COLOR DEFINITIONS
 *-------------------------------------------------------------*/
#define RED 0
#define BLACK 1

/*--------------------------------------------------------------
 *                      STRUCTURE DEFINITION
 *-------------------------------------------------------------*/
/**
 * struct Tree - Represents a single Red-Black Tree node
 * @data   : Integer data stored in the node
 * @color  : Node color (RED / BLACK)
 * @left   : Pointer to the left child
 * @right  : Pointer to the right child
 * @parent : Pointer to the parent node
 */
typedef struct Tree
{
    int data;
    int color;
    struct Tree *left, *right, *parent;
} Tree;

/*--------------------------------------------------------------
 *                      FUNCTION DECLARATIONS
 *-------------------------------------------------------------*/

/* Rotation operations */
void left_rotate(Tree **root, Tree *node);
void right_rotate(Tree **root, Tree *node);

/* Node operations */
Tree *create_node(int data);
int insert_node(Tree **root, int data);
int delete_node(Tree **root, int data);
int delete_tree(Tree **root);

/* Tree balancing & fixing */
void fix_double_black(Tree **root, Tree *node);

/* Search utilities */
int search_node(Tree *root, int data);
Tree *getsibling_node(Tree *node);

/* Display helpers */
void print_color(int color);
void print_tree(Tree *root, int space);

#endif /* TREE_H */
