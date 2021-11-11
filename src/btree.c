#include "btree.h"
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>

/* Utility function to create new binary search tree node
*  Takes an integer x, and creates a new tree_node. Both children are set to NULL
*/
struct tree_node * new_tree_node (int x) {

  struct tree_node *temp = malloc(sizeof (tree_node));
  temp->item = x;
  temp->left = temp->right = NULL;
  return temp;
}

/*Utility function to find minimum value in the binary search tree
* It isn't necessary to search all nodes, only to find the 'leftmost' leaf
*/
struct tree_node* min_node(struct tree_node* t)
{
    struct tree_node* current = t;
 
    //loop to find the leftmost leaf
    while (current && current->left != NULL)
        current = current->left;
 
    return current;
}

struct tree_node * Insert (int x, struct tree_node *t)
{
  // Insert item x into the tree t

  //Base case: Tree is empty
  if (t == NULL) {
    return new_tree_node(x);
  }

  /*Recursive step 1: If the element to be inserted is greater than the root, 
  * the element must be inserted somewhere in the right part of the tree.
  */
  else if (x > t->item) {
    t->right = Insert(x, t->right);
  }
  /*Recursive step 2: If the element to be inserted is lesser than or equal to the root, 
  * the element must be inserted somewhere in the left part of the tree.
  */
  else {
    t->left = Insert(x, t->left);
  }

  return t;
}

struct tree_node * Remove (int x, struct tree_node *t)
{
 // Remove one item from the tree t

  //Base case: The tree is empty => nothing happens
  if (t == NULL)
  {
    return t;
  }  

  /*Recursive step 1: If the element's value to be removed is lesser than the root's value, 
  * the left part of the current root must be examined.
  */
  else if (x < t->item) {
      t->left = Remove(x,t->left);
  }

  /*Recursive step 2: If the element to be removed is greater than the root, 
  * the right part of the current root must be examined.
  */
  else if (x > t->item)
    t->right = Remove(x, t->right);

  // If the element is found, the root's children are examined
  else
  {
    /* If the root only has a right child, this right child is returned as temp, 
    *  and the root is freed. 
    */
    if (t->left == NULL) {
      struct tree_node* temp = t->right;
      free(t);
      return temp;
    }
    
    /* If the root only has a left child, this left child is returned as temp, 
    *  and the root is freed. 
    */
    else if (t->right == NULL) {
      struct tree_node* temp = t->left;
      free(t);
      return temp;      
    }

    /* If the root has both a left and a right child, the one with the lowest value is found.  
    *  Then the element to be removed is copied to temp, which is then removed through
    *  another recursive step.  
    */
    else {
      struct tree_node* temp = min_node(t->right);
      t->item = temp->item;
      t->right = Remove(temp->item, t->right);
    }
  }

  //If the value doesn't exist in the tree, nothing happens
  return t;
}


int Contains (int x, struct tree_node *t)
{

  // Return true if the tree t contains item x. Return false otherwise.
  if (x == t->item)
    return 1;

  /*Recursive step 1: If the element's value to be removed is lesser than the root's value, 
  * the left part of the current root must be examined.
  */
  else if (x < t->item) {
    if (t->left == NULL)
      return 0;
    else 
      return Contains(x, t->left);
  }

  /*Recursive step 2: If the element to be removed is greater than the root, 
  * the right part of the current root must be examined.
  */
  else {
    if (t->right == NULL)
      return 0;
    else 
      return Contains(x, t->right);
  }
}

struct tree_node * Initialize (struct tree_node *t)
{
  // Create an empty tree

  return t = NULL;

}

int Empty (struct tree_node *t)
{
  // Test if empty

  /* If nothing has not yet been inserted in the tree, t will still point to NULL.
  *  Returns false (0) otherwise.
  */
  if (t == NULL)
    return 1;

  else
    return 0;
}

int Full (struct tree_node *t)
{
    // Test if full

    //the tree cannot be full as it is implemented as a linked list

    return 0;
}