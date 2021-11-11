#include <stdio.h>
#include <stdlib.h>
#include <assert.h>		/* assert */
#include <math.h>
#include <malloc.h>

typedef struct tree_node
{
  int item;
  struct tree_node *left;
  struct tree_node *right;
}tree_node;

/* Utility function to create new binary search tree node
*  Takes an integer x, and creates a new tree_node. Both children are set to NULL
*/
struct tree_node * new_tree_node (int x) {

  struct tree_node *temp = (tree_node*) malloc(sizeof (tree_node));
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
  if (t->item == NULL && t->left == NULL && t->right == NULL)
  {
    return t;
  }  

  /*Recursive step 1: If the element to be removed is lesser than or equal to the root, 
  * the left part of the current root must be examined.
  */
  else if (x < t->item) {
    if (t->left == NULL) {
      struct tree_node* temp = t->left;
      free(t);
      return temp;
    }
      
    else 
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

  else if (x < t->item) {
    if (t->left == NULL)
      return 0;
    else 
      return Contains(x, t->left);
  }

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
  //Both the item of the root and both the childrens are NULL
  t = (tree_node*) malloc(sizeof (tree_node));
  t->item = NULL;
  t->left = NULL;
  t->right = NULL;

  return t;
}

int Empty (struct tree_node *t)
{
  // Test if empty

  /* If nothing has not yet been inserted in the tree, the item of the root will still be NULL.
  *  Returns false (0) otherwise.
  */
  if (t->item == NULL && t->left == NULL && t->right == NULL)
    return 1;

  else
    return 0;
}

int Full (struct tree_node *t)
{
    // Test if full

    //the tree cannot be full

    return 0;
}


int main(int argc, char **argv)
{
  // Add your tests here you can use the REQUIRE() statement
	
	  /*
     //               20
     //             /    \
     //            /      \
     //           5       30
     //         /   \     /\
     //        /     \   /  \
     //       1      15 25  40
     //            /          \
     //           /            \
     //          9             45
     //        /   \          /
     //       /     \        /
     //      7      12      42
   */
  struct tree_node *root = NULL;
  int x;

  //Testing law A
  root = Initialize (root);

  x = Empty(root);
  printf("Testing law A \n    x equals %d and should equal 1 \n\n", x);

  //Testing law B
  root = Insert(5, root);
  root = Remove(5,root);
  x = Empty(root);
  printf("Testing law B \n    x equals %d and should equal 1 \n\n", x);

  //Testing law C and empty function for non-empty tree
  printf("Testing law C and empty function for non-empty tree \n");
  root = Insert (20, root);
  root = Insert (5, root);
  root = Insert (1, root);
  root = Insert (15, root);
  root = Insert (9, root);
  root = Insert (7, root);
  root = Insert (12, root);
  root = Insert (30, root);
  root = Insert (25, root);
  root = Insert (40, root);
  root = Insert (45, root);
  root = Insert (42, root);
  
  x = Empty(root);
  printf("    x equals %d and should equal 0 \n", x); 
  x = Contains (20, root);
  printf("    x equals %d and should equal 1 \n", x);
  x = Contains (5, root);
  printf("    x equals %d and should equal 1 \n", x);
  x = Contains (1, root);
  printf("    x equals %d and should equal 1 \n", x);
  x = Contains (15, root);
  printf("    x equals %d and should equal 1 \n", x);
  x = Contains (9, root);
  printf("    x equals %d and should equal 1 \n", x);
  x = Contains (7, root);
  printf("    x equals %d and should equal 1 \n", x);
  x = Contains (12, root);
  printf("    x equals %d and should equal 1 \n", x);
  x = Contains (30, root);
  printf("    x equals %d and should equal 1 \n", x);
  x = Contains (25, root);
  printf("    x equals %d and should equal 1 \n", x);
  x = Contains (40, root);
  printf("    x equals %d and should equal 1 \n", x);
  x = Contains (45, root);
  printf("    x equals %d and should equal 1 \n", x);
  x = Contains (42, root);
  printf("    x equals %d and should equal 1 \n", x);
  x = Contains (2, root);
  printf("    x equals %d and should equal 0 \n", x);
  x = Contains (3, root);
  printf("    x equals %d and should equal 0 \n \n", x);

  //Testing law D
  printf("Testing law D\n");
  root = Remove(40, root);
  x = Contains(42, root);
  printf("    x equals %d and should equal 1 \n", x);
  x = Contains(40, root);
  printf("    x equals %d and should equal 0 \n\n", x);

  //Testing law E
  printf("Testing law E\n");
  root = Insert (-1, root);
  root = Insert (-1, root);
  root = Remove (-1, root);
  x = Contains (-1, root);
  printf("    x equals %d and should equal 1 \n", x);
  root = Remove (-1, root);
  x = Contains (-1, root);
  printf("    x equals %d and should equal 0 \n\n", x);


  //Emptying tree completely
  printf("Emptying tree and testing Remove function non-existent values  \n");
  root = Remove (20, root);
  root = Remove (5, root);
  root = Remove (1, root);
  root = Remove (15, root);
  root = Remove (9, root);
  root = Remove (7, root);
  root = Remove (12, root);
  root = Remove (30, root);
  root = Remove (25, root);
  root = Remove (40, root);
  root = Remove (45, root);
  root = Remove (42, root);

  x = Empty(root);
  printf("    x equals %d and should equal 1 \n\n", x);

  free (root);
  return 0;
}