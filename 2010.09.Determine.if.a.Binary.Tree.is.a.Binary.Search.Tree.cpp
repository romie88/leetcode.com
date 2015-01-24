/**
 * http://leetcode.com/2010/09/determine-if-binary-tree-is-binary.html
 * Determine if a Binary Tree is a Binary Search Tree (BST)
 *
 * September 14, 2010 in binary tree
 * 
 * Write a function isBST(BinaryTree *node) to verify if a given binary tree
 * is a Binary Search Tree (BST) or not.
 */

#include <iostream>
#include <cassert>
#include <limits>

struct Node {
    int    val;
    Node * left;
    Node * right;
    Node( int v ) : val( v ), left( nullptr ), right( nullptr ) {}
};

bool is_bst( const Node * p, bool & is_empty, int & min, int & max ) {
    
    if ( ! p ) {
        is_empty = true;
        return true;
    }

    int left_min, left_max;
    bool left_is_empty;
    bool left_is_bst = is_bst( p->left, left_is_empty, left_min, left_max );
    
    int right_min, right_max;
    bool right_is_empty;
    bool right_is_bst = is_bst( p->right, right_is_empty, right_min, right_max );

    if ( left_is_bst && right_is_bst ) {
        if ( ( left_is_empty || left_max < p->val )
          && ( right_is_empty || right_min > p->val ) ) {
            is_empty = false;
            min = left_min;
            max = right_max;
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool is_bst( const Node * root ) {

    bool is_empty;
    int min, max;

    return is_bst( root, is_empty, min, max );
}

//Method 1 from leetcode.com
//narrow the allowed range of subtrees
bool is_bst_1_impl( const Node * p, int low, int high ) {
    
    if ( ! p ) return true;

    return p->val > low
        && p->val < high
        && is_bst_1_impl( p->left, low, p->val )
        && is_bst_1_impl( p->right, p->val, high );
}

bool is_bst_1( const Node * root ) {

    return is_bst_1_impl( root, 
                          std::numeric_limits< int >::min(),
                          std::numeric_limits< int >::max() );
}

//Method 2 from leetcode.com
//inorder traversal to see if all the values are increasing
bool is_bst_2_impl( const Node * p,
                    int & prev ) {

    if ( ! p ) return true;

    if ( is_bst_2_impl( p->left, prev ) ) {
        if ( p->val > prev ) {
            prev = p->val;
            return is_bst_2_impl( p->right, prev );
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool is_bst_2( const Node * root ) {
    
    int prev = std::numeric_limits< int >::min();
    return is_bst_2_impl( root, prev );
}

int main() {

    {
        /*
    10
   /  \
  5   15     -------- binary tree (1)
     /  \
    6    20
         */
        Node n1( 10 );
        Node n2( 5  );
        Node n3( 15 );
        Node n4( 6  );
        Node n5( 20 );

        n1.left  = &n2;
        n1.right = &n3;

        n3.left  = &n4;
        n3.right = &n5;

        assert( false == is_bst( &n1 ) );
        assert( false == is_bst_1( &n1 ) );
        assert( false == is_bst_2( &n1 ) );
    }
    
    {
        /*
    10
   /  \
  5   15     -------- binary tree (1)
     /  \
    12   20
         */
        Node n1( 10 );
        Node n2( 5  );
        Node n3( 15 );
        Node n4( 12 );
        Node n5( 20 );

        n1.left  = &n2;
        n1.right = &n3;

        n3.left  = &n4;
        n3.right = &n5;

        assert( true == is_bst( &n1 ) );
        assert( true == is_bst_1( &n1 ) );
        assert( true == is_bst_2( &n1 ) );
    }
    
    return 0;
}
