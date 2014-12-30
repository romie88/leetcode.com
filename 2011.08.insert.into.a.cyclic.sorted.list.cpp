/**
 * http://leetcode.com/2011/08/insert-into-a-cyclic-sorted-list.html
 * Insert into a Cyclic Sorted List
 *
 * 2011-08-12 linked list
 *
 * Given a node from a cyclic linked list which has been sorted, write a function to insert a value into the list such that it remains a cyclic sorted list. The given node can be any single node in the list.
 */

/**
 * EDIT:
Thanks to dear readers Saurabh and reader who pointed out my mistake. When the list has only one value, inserting a different value would be handled by case 3), not case 1). Besides, I believe I did not explain “What is a cyclic sorted list” nicely, as this had caused some confusion. Imagine you have a sorted list, but its tail points back to its head. In other words, the list must have a minimum node, continue in a non-descending order, and eventually points back to this minimum node itself. And the only way to access the list is via aNode, which can point to any node in the list and does not necessarily point to the minimum node.

First, it is important that you understand what a cyclic linked list is. A cyclic linked list differs from a normal linked list in that its tail node points back to its head node instead of NULL.

This problem seems a little tricky because the given node is not necessarily the list’s head (ie, the node that has the smallest element). It shouldn’t take you too long to come up with an idea, but beware. There are hidden traps around the corner and you are bound to make some mistakes if you are not careful in your thoughts.

A cyclic sorted linked list. Note that the tail is pointing back to its head. The only reference to the list is a given node which can be any node in the list. Let’s say that you need to insert 4 into the list.

This is how the cyclic list becomes after inserting 4. Note that the cyclic linked list remained in sorted order.

Hints:
It is best to list all kinds of cases first before you jump into coding. Then, it is much easier to reduce the number of cases your code need to handle by combining some of them into a more generic case. Try to also list down all possible edge cases if you have time. You might discover a bug before you even start coding!

Solution:
Basically, you would have a loop that traverse the cyclic sorted list and find the point where you insert the value (Let’s assume the value being inserted called x). You would only need to consider the following three cases:

prev→val ≤ x ≤ current→val:
Insert between prev and current.
x is the maximum or minimum value in the list:
Insert before the head. (ie, the head has the smallest value and its prev→val > head→val.
Traverses back to the starting point:
Insert before the starting point.
Most people have no problem getting case 1) working, while case 2) is easy to miss or being handled incorrectly. Case 3), on the other hand is more subtle and is not immediately clear what kind of test cases would hit this condition. It seemed that case 1) and 2) should take care of all kinds of cases and case 3) is not needed. Think again… How can you be sure of that? Could you come up with one case where it hits case 3)?

Q: What if the list has only one value?
A: Handled by case 1). Handled by case 3).
Q: What if the list is passed in as NULL?
A: Then handle this special case by creating a new node pointing back to itself and return.
Q: What if the list contains all duplicates?
A: Then it has been handled by case 3).
Below is the code. You could combine both negation of case 1) and case 2) in the while loop’s condition, but I prefer to use break statements here to illustrate the above idea clearer.


1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
void insert(Node *& aNode, int x) {
  if (!aNode) {
    aNode = new Node(x);
    aNode->next = aNode;
    return;
  }
 
  Node *p = aNode;
  Node *prev = NULL;
  do {
    prev = p;
    p = p->next;
    if (x <= p->data && x >= prev->data) break;   // For case 1)
    if ((prev->data > p->data) && (x < p->data || x > prev->data)) break; // For case 2)
  } while (p != aNode);   // when back to starting point, then stop. For case 3)
 
  Node *newNode = new Node(x);
  newNode->next = p;
  prev->next = newNode;
}
 *
 */

#include <iostream>

struct Node {
    int val;
    Node * next;
    Node( int v ) : val( v ), next( nullptr ) {}
};

Node * insert_into_cyclic_sorted_list( Node * p, int n ) {
    
    Node * q = new Node( n );

    if ( p == nullptr ) {
        q->next = q;
        return q;
    }

    Node * t = p;
    while ( t->next != p && t->next->val >= t->val )
        t = t->next;

    //t points the node which has the maximum value
    Node * t2 = t;
    while ( t2->next != t && n > t2->next->val )
        t2 = t2->next;

    Node * tmp = t2->next;
    t2->next = q;
    q->next = tmp;
    
    return q;
}

void print_cyclic_list( Node * p ) {
    Node * t = p;
    do {
        std::cout << t->val << " ";
        t = t->next;
    } while ( t != p );
    std::cout << std::endl;
}

void insert_into_cyclic_sorted_list2( Node * & p, int n ) {
    
    if ( p == nullptr ) {
        p = new Node( n );
        p->next = p;
        return;
    }

    Node * t = p->next;
    while ( t != p ) {
        
        if ( t->val <= n && t->next->val >= n ) break;
        if ( t->val > t->next->val//t points to the maximum node
          && ( n >= t->val || n <= t->next->val ) ) break;
        
        t = t->next;
    }
    
    Node * tmp = t->next;
    t->next = new Node( n );
    t->next->next = tmp;
}

int main() {
    
    Node n1( 1 );
    Node n2( 3 );
    Node n3( 5 );
    Node n4( 7 );
    
    n1.next = &n2;
    n2.next = &n3;
    n3.next = &n4;
    n4.next = &n1;
    
    print_cyclic_list( &n1 );
    
    Node * p = &n2;
    insert_into_cyclic_sorted_list2( p, 2 );

    print_cyclic_list( &n1 );

    insert_into_cyclic_sorted_list2( p, 9 );

    print_cyclic_list( &n1 );

    return 0;
}
