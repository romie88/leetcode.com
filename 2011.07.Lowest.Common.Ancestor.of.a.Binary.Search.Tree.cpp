/**
 * http://leetcode.com/2011/07/lowest-common-ancestor-of-a-binary-search-tree.html
 * Lowest Common Ancestor of a Binary Search Tree (BST)
 *
 * July 17, 2011 in binary tree
 *
 * Given a binary search tree (BST), find the lowest common ancestor of two
 * given nodes in the BST.
 */

//assume the BST has the following property:
//all the nodes of the left subtree have values <= the current node
//all the nodes of the right subtree have values > the current node
//after a second thought
//if it is allowed that a binary search tree has duplicate values on the
//left subtree then the binary search tree cannot keep balanced.
//A binary search tree cannot have duplicated key values!!!

#include <iostream>
#include <cassert>

struct Node {
    int    val;
    Node * left;
    Node * right;
    Node( int v ) : val( v ), left( nullptr ), right( nullptr ) {}
};

bool is_in_bt( const Node * p,
               const Node * t ) {

    if ( ! p || ! t ) return false;
    else if ( p == t ) return true;
    else return is_in_bt( p->left, t ) || is_in_bt( p->right, t );
}

const Node * lca_bst( const Node * root,
                      const Node * p1,
                      const Node * p2 ) {
    
    if ( ! root || ! p1 || ! p2 ) return nullptr;

    //for now assume p1 and p2 are in the given bst
    const Node * p = root;
    while ( p ) {

        if ( p == p1 || p == p2 ) {
            break;
        } else if ( p->val >= std::max( p1->val, p2->val ) ) {
            //p1 and p2 are in the left subtree
            p = p->left;
        } else if ( p->val < std::min( p1->val, p2->val ) ) {
            //p1 and p2 are in the right subtree
            p = p->right;
        } else {
            //p is the lca
            break;
        }
    }
    
    if ( ! p ) return nullptr;

    if ( is_in_bt( p, p1 ) && is_in_bt( p, p2 ) )
        return p;
    else
        return nullptr;
}

int main() {
    
    {
        /*
        _______6______
       /              \
    ___2__          ___8__
   /      \        /      \
   0      _4       7       9
         /  \
         3   5
         */
        Node n1( 6 );
        Node n2( 2 );
        Node n3( 8 );
        Node n4( 0 );
        Node n5( 4 );
        Node n6( 7 );
        Node n7( 9 );
        Node n8( 3 );
        Node n9( 5 );

        n1.left  = &n2;
        n1.right = &n3;
        n2.left  = &n4;
        n2.right = &n5;
        n3.left  = &n6;
        n3.right = &n7;
        n5.left  = &n8;
        n5.right = &n9;

        const Node * p = lca_bst( &n1, &n8, &n9 );
        assert( p == &n5 );
        
        p = lca_bst( &n1, &n2, &n8 );
        assert( p == &n2 );
        
        p = lca_bst( &n1, &n7, &n9 );
        assert( p == &n1 );

        Node n10( 10 );
        p = lca_bst( &n1, &n2, &n10 );
        assert( p == nullptr );
    }
    
    return 0;
}
