/**
 * http://leetcode.com/2011/07/lowest-common-ancestor-of-a-binary-tree-part-i.html
 * Lowest Common Ancestor of a Binary Tree Part I
 *
 * July 18, 2011 in binary tree
 *
 * Given a binary tree, find the lowest common ancestor of two given nodes in
 * the tree.
 */

#include <iostream>
#include <vector>
#include <cassert>

struct Node {
    int    val;
    Node * left;
    Node * right;
    Node( int v ) : val( v ), left( nullptr ), right( nullptr ) {}
};

bool find_path( const Node * root,
                const Node * p,
                std::vector< const Node * > & path ) {

    if ( root == nullptr ) return false;

    path.push_back( root );
    if ( root == p ) 
        return true;
    
    if ( find_path( root->left, p, path )
      || find_path( root->right, p, path ) ) {
        return true;
    } else {
        path.pop_back();
        return false;
    }
}

//Method 1
//find both paths from root to p1 and p2 respectively and save them in vectors
//find the last common element of the two vectors
const Node * lca_bt_1( const Node * root,
                       const Node * p1,
                       const Node * p2 ) {
    
    std::vector< const Node * > path1;
    std::vector< const Node * > path2;

    if ( ! find_path( root, p1, path1 ) || ! find_path( root, p2, path2 ) )
        return nullptr;

    auto it1 = path1.begin();
    auto it2 = path2.begin();
    for ( ; it1 != path1.end() && it2 != path2.end(); ++it1, ++it2 )
        if ( *it1 != *it2 ) break;

    return *(--it1);
}

//this implementation assumes that both p1 and p2 are truly in the given
//binary tree
const Node * lca_bt_2_impl( const Node * root,
                            const Node * p1,
                            const Node * p2 ) {
    
    if ( ! root || ! p1 || ! p2 ) return nullptr;

    if ( root == p1 || root == p2 ) return root;
    
    const Node * left_lca  = lca_bt_2_impl( root->left,  p1, p2 );
    const Node * right_lca = lca_bt_2_impl( root->right, p1, p2 );
    
    if ( left_lca && right_lca )
        return root;
    else if ( left_lca )
        return left_lca;
    else
        return right_lca;
}

bool is_descandant( const Node * root, const Node * p ) {
    
    if ( root == nullptr || p == nullptr ) return false;

    if ( root == p ) return true;

    return is_descandant( root->left, p ) || is_descandant( root->right, p );
}

//Method2
//Directly traverse the binary tree
//first assume that both given nodes are truly in the given binary tree
//check the current root; if it matches one of the given node, return;
//if not, recurse into the left subtree and right subtree
//if the result from the left subtree and the result from the right subtree
//are not nullptr, the current root is returned;
//otherwise the result from the left subtree or the right subtree is returned
//according
//However the result must still be verified by checking if p1 and p2 are
//true descandants of the found lca.
const Node * lca_bt_2( const Node * root,
                       const Node * p1,
                       const Node * p2 ) {

    const Node * lca = lca_bt_2_impl( root, p1, p2 );
    
    if ( lca && is_descandant( lca, p1 ) && is_descandant( lca, p2 ) )
        return lca;
    else
        return nullptr;
}

#if 0
//test find_path()
void print_path( const std::vector< const Node * > & path ) {
    for ( const auto x : path )
        std::cout << x->val << " ";
    std::cout << std::endl;
}

int main() {
    
    {
        /*
   _______________28_______________
  /                                \
  4____                        ____69
       \                      /
      __8__                __56__
     /     \              /      \
   __7     12__        __34    __27__
  /            \      /       /      \
  5_          _13    _2      _3      39
    \        /      /       /
     6      11     10       9
        */

        Node n1( 28 );
        Node n2( 4  );
        Node n3( 69 );
        Node n4( 8  );
        Node n5( 56 );
        Node n6( 7  );
        Node n7( 12 );
        Node n8( 34 );
        Node n9( 27 );
        Node n10( 5 );
        Node n11( 13 );
        Node n12( 2  );
        Node n13( 3  );
        Node n14( 39 );
        Node n15( 6  );
        Node n16( 11 );
        Node n17( 10 );
        Node n18( 9  );
                
        n1.left  = &n2;
        n1.right = &n3;
        n2.right = &n4;
        n3.left  = &n5;
        n4.left  = &n6;
        n4.right = &n7;
        n5.left  = &n8;
        n5.right = &n9;
        n6.left  = &n10;
        n7.right = &n11;
        n8.left  = &n12;
        n9.left  = &n13;
        n9.right = &n14;
        n10.right = &n15;
        n11.left  = &n16;
        n12.left  = &n17;
        n13.left  = &n18;
        
        std::vector< const Node * > path;
        
        //test case 1
        path.clear();
        if ( find_path( &n1, &n18, path ) ) {
            print_path( path );
        } else {
            std::cout << "cannot find the path" << std::endl;
        }
        
        //test case 2
        Node n19( 19 );
        path.clear();
        if ( find_path( &n1, &n19, path ) ) {
            print_path( path );
        } else {
            std::cout << "cannot find the path" << std::endl;
        }

    }
    
    return 0;
}
#endif

int main() {
    
    {
        /*
   _______________28_______________
  /                                \
  4____                        ____69
       \                      /
      __8__                __56__
     /     \              /      \
   __7     12__        __34    __27__
  /            \      /       /      \
  5_          _13    _2      _3      39
    \        /      /       /
     6      11     10       9
        */

        Node n1( 28 );
        Node n2( 4  );
        Node n3( 69 );
        Node n4( 8  );
        Node n5( 56 );
        Node n6( 7  );
        Node n7( 12 );
        Node n8( 34 );
        Node n9( 27 );
        Node n10( 5 );
        Node n11( 13 );
        Node n12( 2  );
        Node n13( 3  );
        Node n14( 39 );
        Node n15( 6  );
        Node n16( 11 );
        Node n17( 10 );
        Node n18( 9  );
                
        n1.left  = &n2;
        n1.right = &n3;
        n2.right = &n4;
        n3.left  = &n5;
        n4.left  = &n6;
        n4.right = &n7;
        n5.left  = &n8;
        n5.right = &n9;
        n6.left  = &n10;
        n7.right = &n11;
        n8.left  = &n12;
        n9.left  = &n13;
        n9.right = &n14;
        n10.right = &n15;
        n11.left  = &n16;
        n12.left  = &n17;
        n13.left  = &n18;
        
        Node n19( 19 );

        const Node * p = nullptr;

        p = lca_bt_1( &n1, &n16, &n17 );
        assert( p == &n1 );

        p = lca_bt_1( &n1, &n16, &n10 );
        assert( p == &n4 );
        
        p = lca_bt_1( &n1, &n3, &n9 );
        assert( p == &n3 );
        
        p = lca_bt_1( &n1, &n8, &n19 );
        assert( p == nullptr );
        
        p = lca_bt_2( &n1, &n16, &n17 );
        assert( p == &n1 );

        p = lca_bt_2( &n1, &n16, &n10 );
        assert( p == &n4 );
        
        p = lca_bt_2( &n1, &n3, &n9 );
        assert( p == &n3 );

        p = lca_bt_2( &n1, &n8, &n19 );
        assert( p == nullptr );
    }

    return 0;
}
        
