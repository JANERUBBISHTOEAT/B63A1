/*
   Header file for our AVL tree implementation.

   Author: A. Tafliovich
   Based heavily on materials developed by F. Estrada.

   You will NOT be submitting this file. Your code will be tested with the
   original version of this file, so make sure you do not modify it!
*/

#include<stdio.h>
#include<stdlib.h>

#ifndef __AVL_tree_header
#define __AVL_tree_header

typedef struct avl_node {
  int key;                 // key stored in this node
  void* value;             // value associated with this node's key
  int height;              // height of tree rooted at this node
  struct avl_node* left;   // this node's left child
  struct avl_node* right;  // this node's right child
} AVL_Node;

/* Returns the node, from the tree rooted at 'node', that contains key 'key'.
 * Returns NULL if 'key' is not in the tree.
*/
AVL_Node* search(AVL_Node* node, int key);

/* Inserts the key/value pair 'key'/'value' into the AVL tree rooted at
 * 'node'.  If 'key' is already a key in the tree, updates the value
 * associated with 'key' to 'value'. Returns the root of the resulting tree.
 */
AVL_Node* insert(AVL_Node* node, int key, void* value);

/* Deletes the node with key 'key' from the AVL tree rooted at 'node'.  If
 * 'key' is not a key in the tree, the tree is unchanged. Returns the root of
 * the resulting tree.
*/
AVL_Node* delete(AVL_Node* node, int key);


/* Prints the keys of the AVL tree rooted at 'node', in the in-order
 * traversal order.
 */
void print_tree_inorder(AVL_Node* node);


/* Frees all memory allocated for an AVL tree rooted at 'node'.
 */
void delete_tree(AVL_Node* node);

#endif
