/**
 * http://leetcode.com/2011/07/lowest-common-ancestor-of-a-binary-tree-part-ii.html
 * Lowest Common Ancestor of a Binary Tree Part II
 *
 * July 21, 2011 in binary tree
 *
 * Given a binary tree, find the lowest common ancestor of two given nodes in
 * the tree. Each node contains a parent pointer which links to its parent.
 */

#include <iostream>
#include <unordered_set>
#include <cassert>

struct Node {
    int    val;
    Node * left;
    Node * right;
    Node * parent;
    Node( int v ) : val( v ), left( nullptr ), right( nullptr ), parent( nullptr ) {}
};

//Method 1
//trace back to root and return the first common node of the two paths
const Node * lca_bt_1( const Node * root,
                       const Node * p1,
                       const Node * p2 ) {
    
    if ( ! root  || ! p1 || ! p2 ) return nullptr;
    
    std::unordered_set< const Node * > visited;
    while ( p1 || p2 ) {
        if ( p1 ) {
            if ( ! visited.insert( p1 ).second ) {
                return p1;
            }
            p1 = p1->parent;
        }
        if ( p2 ) {
            if ( ! visited.insert( p2 ).second ) {
                return p2;
            }
            p2 = p2->parent;
        }
    }

    return nullptr;
}

//calculate the steps to go up to reach the root node
int cal_height( const Node * p ) {

    int height = 0;
    while ( p ) {
        ++height;
        p = p->parent;
    }
    return height;
}

//Method 2
const Node * lca_bt_2( const Node * root,/* not used */
                       const Node * p1,
                       const Node * p2 ) {
    
    if ( ! root || ! p1 || ! p2 ) return nullptr;
    
    int h1 = cal_height( p1 );
    int h2 = cal_height( p2 );

    //assume h1 < h2 if not swap 1 with 2
    if ( h1 > h2 ) {
        std::swap( h1, h2 );
        std::swap( p1, p2 );
    }

    int dh = h2 - h1;
    for ( int h = 0; h < dh; ++h )
        p2 = p2->parent;

    while ( p1 && p2 ) {
        if ( p1 == p2 ) return p1;
        p1 = p1->parent;
        p2 = p2->parent;
    }

    return nullptr;//p1 and p2 are not in the same tree
}

int main() {
    
    {
        /*
        _______3______
       /              \
    ___5__          ___1__
   /      \        /      \
   6      _2       0       8
         /  \
         7   4
         */

        Node n1( 3 );
        Node n2( 5 );
        Node n3( 1 );
        Node n4( 6 );
        Node n5( 2 );
        Node n6( 0 );
        Node n7( 8 );
        Node n8( 7 );
        Node n9( 4 );
         
        n1.left  = &n2;
        n1.right = &n3;
        n2.parent = &n1;
        n3.parent = &n1;

        n2.left  = &n4;
        n2.right = &n5;
        n4.parent = &n2;
        n5.parent = &n2;
        
        n3.left  = &n6;
        n3.right = &n7;
        n6.parent = &n3;
        n7.parent = &n3;

        n5.left  = &n8;
        n5.right = &n9;
        n8.parent = &n5;
        n9.parent = &n5;
        
        Node n10( 10 );
        
        const Node * p = nullptr;

        p = lca_bt_1( &n1, &n3, &n5 );
        assert( p == &n1 );

        p = lca_bt_1( &n1, &n2, &n9 );
        assert( p == &n2 );
        
        p = lca_bt_1( &n1, &n3, &n10 );
        assert( p == nullptr );
        
        p = lca_bt_1( &n1, &n5, &n7 );
        assert( p == &n1 );
        
        p = lca_bt_2( &n1, &n3, &n5 );
        assert( p == &n1 );

        p = lca_bt_2( &n1, &n2, &n9 );
        assert( p == &n2 );
        
        p = lca_bt_2( &n1, &n3, &n10 );
        assert( p == nullptr );
        
        p = lca_bt_2( &n1, &n5, &n7 );
        assert( p == &n1 );
    }

    return 0;
}
        
