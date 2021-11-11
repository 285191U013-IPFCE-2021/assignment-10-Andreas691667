#include "linked_list.h"
/*
 * Linked list
 */

#include <stdio.h>		/* printf */
#include <stdlib.h>		/* malloc, free */
#include <assert.h>		/* assert */
#include <math.h>

int square (int x)
{
  return x * x;
}

/* functions to create lists */
node *make_node (int v, node * q)
{
  node *p = (node*) malloc(sizeof (node));
  p->value = v;

  if (q == &SENTINEL_node)
    p->next = &SENTINEL_node;
  else
    p->next = q;
  return p;
}

/* free all nodes in the list p */
void free_list (node * p)
{
  node *q = p;
  while (q != &SENTINEL_node)
    {
      node *t = q->next;
      free (q);
      q = t;
    }

}

/* print list to console */
void print_list (node * p)
{
    // Add your code for exercise 1
    // There is NO testcode for this

    //precondition: List isn't empty
    assert(p != &SENTINEL_node);

    //Base case: The list consists of only one element
    if (p->next == &SENTINEL_node)
      printf("%d", p->value);
    
    //Recursive step: Print the value of the current node, and then the next one
    else {
      printf("%d ", p->value);
      print_list(p->next);
    }

    return;
}

int sum_squares (node * p)
{
    // Add your code for excercise 2
    // You can find the tests in tests.cpp

    //Base case 1: List is empty - the sum of squares will be 0
    if (p == &SENTINEL_node)
    {
      return 0;
    }
    
    //Base case 2: The list consists of only one element
    else if (p->next == &SENTINEL_node)
      return square(p->value);

    /*Recursive step: The nodes are squared and added
    * As adding is commutative, the order in which the squared nodes are added doesn't matter
    */
    else 
      return square(p->value) + sum_squares(p->next);
    
}

node *map (node * p, int (*f) (int))
{
  // Add your code for excercise 3
  if (p == &SENTINEL_node)
    return &SENTINEL_node;
  
  else
    return make_node(f(p->value), map(p->next, f));
  
}