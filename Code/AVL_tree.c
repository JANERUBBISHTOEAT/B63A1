/*
   AVL tree implementation.

   Author: A. Tafliovich
   Based heavily on materials developed by F. Estrada.
*/

#include "AVL_tree.h"

/*************************************************************************
 ** Suggested helper functions
 *************************************************************************/

/* Returns the height (number of nodes on the longest root-to-leaf path) of
 * the tree rooted at node 'node'. Returns 0 if 'node' is NULL.
 */
int height(AVL_Node *node)
{
  return node ? node->height : 0;
}

/* Updates the height of the tree rooted at node 'node' based on the heights
 * of its children. Note: this should be an O(1) operation.
 */
void update_height(AVL_Node *node)
{
  if (node)
  {
    int left_height = height(node->left);
    int right_height = height(node->right);
    node->height = (left_height > right_height ? left_height : right_height) + 1;
  }
}

/* Returns the balance factor (height of left subtree - height of right
 * subtree) of node 'node'. Returns 0 of node is NULL.
 */
int balance_factor(AVL_Node *node)
{
  return node ? height(node->left) - height(node->right) : 0;
}

/* Returns the result of performing the corresponding rotation in the AVL
 * tree rooted at 'node'.
 */
// single rotations: right/clockwise
// need to change the parent's pointer to this node!
AVL_Node *right_rotation(AVL_Node *node)
{
  if (node == NULL)
    return NULL;
  AVL_Node *new_root = node->left;
  node->left = new_root->right;
  new_root->right = node;
  update_height(node);
  update_height(new_root);
  return new_root; // parent's pointer unchanged
}
// single rotations: left/counter-clockwise
// need to change the parent's pointer to this node!
AVL_Node *left_rotation(AVL_Node *node)
{
  if (node == NULL)
    return NULL;
  AVL_Node *new_root = node->right;
  node->right = new_root->left;
  new_root->left = node;
  update_height(node);
  update_height(new_root);
  return new_root;
}
// double rotation: right/clockwise then left/counter-clockwise
AVL_Node *right_left_rotation(AVL_Node *node)
{
  if (node == NULL)
    return NULL;
  node->right = right_rotation(node->right); // parent's pointer changed
  return left_rotation(node);
}
// double rotation: left/counter-clockwise then right/clockwise
AVL_Node *left_right_rotation(AVL_Node *node)
{
  if (node == NULL)
    return NULL;
  node->left = left_rotation(node->left); // same
  return right_rotation(node);
}

/* Returns the successor node of 'node'. */
AVL_Node *successor(AVL_Node *node)
{
  if (node == NULL)
    return NULL;
  AVL_Node *current = node->right;
  while (current->left != NULL)
    current = current->left;
  return current;
}

/* Creates and returns an AVL tree node with key 'key', value 'value', height
 * of 1, and left and right subtrees NULL.
 */
AVL_Node *create_node(int key, void *value)
{
  AVL_Node *node = (AVL_Node *)malloc(sizeof(AVL_Node));
  node->key = key;
  node->value = value;
  node->height = 1;
  node->left = NULL;
  node->right = NULL;
  return node;
}

/*************************************************************************
 ** Provided functions
 *************************************************************************/
void print_tree_inorder_(AVL_Node *node, int offset)
{
  if (node == NULL)
    return;
  print_tree_inorder_(node->right, offset + 1);
  printf("%*s %d [%d]\n", offset, "", node->key, node->height);
  print_tree_inorder_(node->left, offset + 1);
}

void print_tree_inorder(AVL_Node *node)
{
  print_tree_inorder_(node, 0);
}

void delete_tree(AVL_Node *node)
{
  if (node == NULL)
    return;
  delete_tree(node->left);
  delete_tree(node->right);
  free(node);
}

/*************************************************************************
 ** Required functions
 ** Must run in O(log n) where n is the number of nodes in a tree rooted
 **  at 'node'.
 *************************************************************************/

AVL_Node *search(AVL_Node *node, int key)
{
  if (node == NULL) // no tree
    return NULL;
  if (key == node->key)
    return node;
  if (key < node->key)
    return search(node->left, key);
  else
    return search(node->right, key);
}

AVL_Node *insert(AVL_Node *node, int key, void *value)
{
  if (node == NULL)
    return create_node(key, value);
  if ((search(node, key)) != NULL) // key already exists
    return node;
  if (key < node->key)
    node->left = insert(node->left, key, value);
  else
    node->right = insert(node->right, key, value);

  int balance = balance_factor(node);
  if (balance > 1) // left heavy
  {
    if (key < node->left->key) // left-left case
      return right_rotation(node);
    else // left-right case
      return left_right_rotation(node);
  }
  else if (balance < -1) // right heavy
  {
    if (key > node->right->key) // right-right case
      return left_rotation(node);
    else // right-left case
      return right_left_rotation(node);
  }

  update_height(node);
  return node;
}

AVL_Node *delete(AVL_Node *node, int key)
{
  if (node == NULL)
    return NULL;
  if (key < node->key)
    node->left = delete(node->left, key);
  else if (key > node->key)
    node->right = delete(node->right, key);
  else // found
  {
    if (node->left == NULL && node->right == NULL) // no children
    {
      free(node);
      return NULL;
    }
    else if (node->left == NULL) // only right child
    {
      AVL_Node *tmp = node->right;
      free(node);
      return tmp;
    }
    else if (node->right == NULL) // only left child
    {
      AVL_Node *tmp = node->left;
      free(node);
      return tmp;
    }
    else // two children
    {
      AVL_Node *tmp = successor(node);
      node->key = tmp->key;
      node->value = tmp->value;
      node->right = delete(node->right, tmp->key); // delete successor
      // note: successor has no left child
      // also, we don't have a parent pointer, so we can't just free it
      // instead, we recursively call delete on the right subtree
      // this is a bit inefficient, but it's the only way without the parent pointer
    }
  }

  int balance = balance_factor(node);
  if (balance > 1) // left heavy
  {
    if (balance_factor(node->left) >= 0) // left-left case
      return right_rotation(node);
    else // left-right case
      return left_right_rotation(node);
  }
  else if (balance < -1) // right heavy
  {
    if (balance_factor(node->right) <= 0) // right-right case
      return left_rotation(node);
    else // right-left case
      return right_left_rotation(node);
  }

  update_height(node);
  return node;
}
