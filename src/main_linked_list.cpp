extern "C"{
    // Add the header files required to run your main 
    // #include "C:\Users\Andreas\Desktop\VSCode\Afleveringer\assignment-10-Andreas691667\include\linked_list.h"
}

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>		/* assert */
#include <math.h>
#include <malloc.h>

typedef struct node
{
   int value;
   struct node * next;
} node;

/* terminal node at the end of the list */
static node SENTINEL_node = {0,0};

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
node* free_list (node * p)
{
  node *q = p;
  while (q != &SENTINEL_node)
    {
      node *t = q->next;
      free (q);
      q = t;
    }
  return q;
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

// File for sandboxing and trying out code
int main(int argc, char **argv)
{
    	//exercise 2
    	int sum;
      node *ns = NULL;
    	ns = make_node (1,
			make_node (2,
				   make_node (3,
					      make_node (4,
							  make_node (5,
								    &SENTINEL_node)))));

	sum = sum_squares (ns);	/* sum should equal 55 */

    printf("Sum is %d and should be 55\n", sum);

  free_list(ns);
      
	sum=sum_squares(ns);

  printf("Sum is %d and should be 0\n", sum);

	ns = make_node (1,&SENTINEL_node);
	sum=sum_squares(ns);

    printf("Sum is %d and should be 1\n", sum);

	//exercise 3
	//ns contains one node with the value 1

    //ns is 1-> SENT
	node *mns = map (ns, square);
	sum=sum_squares(ns);

    printf("Sum of ns is %d and should be 1 \n", sum);
     //1 = 1

	free_list(ns);
  	ns = make_node (1,
			make_node (2,
				   make_node (3,
					      &SENTINEL_node)));
	//ns is 1->2->3->SENT
  	mns = map (ns, square);
    //mns is 1->4->9->SENT

    sum = sum_squares(ns);
    //1+4+9 = 14
    printf("Sum of ns is %d and should be 14 \n", sum);

	sum=sum_squares(mns);
	//1+16+81 = 98
    printf("Sum of mns is %d and should be 98 \n", sum);

	free_list(ns);
    
    return 0;
}