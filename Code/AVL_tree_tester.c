/*
  Some light testing of our AVL tree implementation.

  To run:
    AVL_tree_tester sample_input.txt
  or
    AVL_tree_tester

  Author: A. Tafliovich
  Based heavily on materials developed by F. Estrada.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AVL_tree.h"

#define MAX_LIMIT 1024

AVL_Node* create_tree(FILE* f);
void test_tree(AVL_Node* root);
void print_tree_report(AVL_Node* root);

int main(int argc, char* argv[]) {
  AVL_Node* root = NULL;

  // If user specified a file for reading, create a tree with keys from it.
  if (argc > 1) {
    FILE* f = fopen(argv[1], "r");
    if (f == NULL) {
      fprintf(stderr, "Unable to open the specified input file: %s\n", argv[1]);
      exit(0);
    }
    root = create_tree(f);
    fclose(f);
  } else {
    printf("You did not specify an input file.");
    printf(" We will start with an empty tree.\n");
  }

  test_tree(root);
  return 0;
}

AVL_Node* create_tree(FILE* f) {
  char line[1024];
  int key;
  AVL_Node* root = NULL;

  while (fgets(&line[0], MAX_LIMIT, f)) {  // read the next line
    key = atoi(&line[0]);
    printf("read %d\n", key);
    root = insert(root, key, NULL);  // no values for this simple tester
    print_tree_report(root);
  }
  return root;
}

void test_tree(AVL_Node* root) {
  char line[1024];
  AVL_Node* node;

  while (1) {
    printf("Choose a command: (s)earch, (i)nsert, (d)elete, (q)uit\n");
    fgets(&line[0], MAX_LIMIT, stdin);
    if (line[0] == 'q') {  // quit
      printf("Quit selected. Goodbye!\n");
      delete_tree(root);
      return;
    }
    if (line[0] == 's') {  // search
      printf("Search selected. Enter key to search for: ");
      fgets(&line[0], MAX_LIMIT, stdin);
      node = search(root, atoi(&line[0]));
      if (node != NULL) {
        printf("Key %d was found at height %d.\n", node->key, node->height);
      } else {
        printf("This key is not in the tree.\n");
      }
    } else if (line[0] == 'i') {  // insert
      printf("Insert selected. Enter key to insert");
      printf(" (no values in this simple tester): ");
      fgets(&line[0], MAX_LIMIT, stdin);
      root = insert(root, atoi(&line[0]), NULL);
      print_tree_report(root);
    } else if (line[0] == 'd') {  // delete
      printf("Delete selected. Enter key to delete: ");
      fgets(&line[0], MAX_LIMIT, stdin);
      root = delete(root, atoi(&line[0]));
      print_tree_report(root);
    }
  }
}

void print_tree_report(AVL_Node* root) {
  printf("** The tree is now:\n");
  print_tree_inorder(root);
  printf("**\n");
}
