/**
 * http://leetcode.com/2010/11/largest-binary-search-tree-bst-in.html
 * Largest Subtree Which is a Binary Search Tree (BST)
 *
 * November 18, 2010 by binary tree
 *
 * Given a binary tree, find the largest subtree which is a Binary Search Tree
 * (BST), where largest means subtree with largest number of nodes in it.
 */

#include <iostream>
#include <cassert>

struct Node {
    int    val;
    Node * left;
    Node * right;
    Node( int v ) : val( v ), left( nullptr ), right( nullptr ) {}
};

void find_largest_sub_bst_impl( const Node * p,//current root
                                        const Node * & mp,//largest subtree root
                                        int & mn,//largest subtree node number
                                        bool & is_empty,//if current tree is empty
                                        int & max,//max value in the current tree
                                        int & min,//min value in the current tree
                                        bool & is_bst//current tree is bst or not
                                        ) {
    
    if ( ! p ) {
        mp = nullptr;
        mn = 0;
        is_empty = true;
        is_bst = true;
        return;
    }
    
    const Node * left_mp  = nullptr;
    const Node * right_mp = nullptr;
    int left_mn  = 0;
    int right_mn = 0;
    bool left_is_empty  = false;
    bool right_is_empty = false;
    int left_max;
    int right_max;
    int left_min;
    int right_min;
    bool left_is_bst  = false;
    bool right_is_bst = false;

    find_largest_sub_bst_impl( p->left, left_mp, left_mn, left_is_empty, left_max, left_min, left_is_bst );
    find_largest_sub_bst_impl( p->right, right_mp, right_mn, right_is_empty, right_max, right_min, right_is_bst );
    
    std::cout << "================" << std::endl;
    if ( left_mp )
    std::cout << "left_mp = " << left_mp->val << std::endl;
    else
    std::cout << "left_mp = " << "nullptr" << std::endl;

    std::cout << "left_mn = " << left_mn << std::endl;
    std::cout << "left_is_empty = " << left_is_empty << std::endl;
    std::cout << "left_is_bst = " << left_is_bst << std::endl;
    
    if ( right_mp )
    std::cout << "right_mp = " << right_mp->val << std::endl;
    else
    std::cout << "right_mp = " << "nullptr" << std::endl;

    std::cout << "right_mn = " << right_mn << std::endl;
    std::cout << "right_is_empty = " << right_is_empty << std::endl;
    std::cout << "right_is_bst = " << right_is_bst << std::endl;

    if ( left_is_empty ) {
        if ( right_is_empty ) {
            mp = p;
            mn = 1;
            is_empty = false;
            max = p->val;
            min = p->val;
            is_bst = true;
        } else {
            //left is empty but right is not empty
            if ( right_is_bst && p->val < right_min ) {
                mp = p;
                mn = 1 + right_mn;
                is_empty = false;
                max = right_max;
                min = p->val;
                is_bst = true;
            } else {
                mp = right_mp;
                mn = right_mn;
                is_empty = false;
                is_bst = false;
            }
        }
    } else if ( right_is_empty ) {
        //left is not empty
        if ( left_is_bst && p->val > left_max ) {
            mp = p;
            mn = 1 + left_mn;
            is_empty = false;
            max = p->val;
            min = left_min;
            is_bst = true;
        } else {
            mp = left_mp;
            mn = left_mn;
            is_empty = false;
            is_bst = false;
        }
    } else {
        
        if ( left_is_bst && right_is_bst && p->val > left_max && p->val < right_min ) {
            mp = p;
            mn = 1 + left_mn + right_mn;
            is_empty = false;
            max = right_max;
            min = left_min;
            is_bst = true;
        } else {
            
            mp = left_mn > right_mn ? left_mp : right_mp;
            mn = left_mn > right_mn ? left_mn : right_mn;
            is_empty = false;
            is_bst = false;

        }
    }
}

const Node * find_largest_sub_bst( const Node * root ) {

    const Node * mp;
    int mn;
    bool is_empty;
    int max;
    int min;
    bool is_bst;
    find_largest_sub_bst_impl( root,//current root
                               mp,//largest subtree root
                               mn,//largest subtree node number
                               is_empty,//if current tree is empty
                               max,//max value in the current tree
                               min,//min value in the current tree
                               is_bst//current tree is bst or not
                              );
    return mp;
}

int main() {
    
    {
        Node n1( 10 );
        Node n2( 5 );
        Node n3( 15 );
        Node n4( 1 );
        Node n5( 8 );
        Node n6( 7 );

        n1.left  = &n2;
        n1.right = &n3;
        n2.left  = &n4;
        n2.right = &n5;
        n3.right = &n6;

        const Node * p = find_largest_sub_bst( &n1 );

        assert( p == &n2 );
    }

    return 0;
}

