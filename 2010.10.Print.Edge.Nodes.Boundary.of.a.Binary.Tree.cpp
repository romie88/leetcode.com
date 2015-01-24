#include <iostream>
#include <stack>

/**
 * Definition of left-most node
 * If a node is a left-most node, then its left child must be a left-most node
 * as well.
 * If its left child does not exist, then its right child will be a left-most
 * node.
 */

struct Node {
    int     val;
    Node  * left;
    Node  * right;
    Node( int v ) : val( v ), left( 0 ), right( 0 ) {}
};

void postorder_print_leaf( const Node * p ) {
    
    if ( ! p ) return;

    postorder_print_leaf( p->left );
    postorder_print_leaf( p->right );
    if ( ! p->left && ! p->right )
        std::cout << p->val << ' ';
}

//my iterative method
void print_edge_iterative( const Node * root ) {

    //print all the left most node
    const Node * p = root;
    while ( p ) {
        if ( p->left || p->right )
            //if p is a leaf node we skip the print because
            //it will be printed in the leaf nodes print part
            std::cout << p->val << ' ';
        //p = p->left;
        //to avoid the left most node ambiguity
        if ( p->left )
            p = p->left;
        else
            p = p->right;
    }
    
    postorder_print_leaf( root );
    
    //print all the right most node
    //use a stack here to reverse the order of printing
    std::stack< const Node * > s;
    p = root;
    while ( p ) {
        if ( p->left || p->right )
            //the same reason as before
            //if p is a leaf node we skip the print because
            //it has been printed in the leaf nodes print part
            s.push( p );
        //p = p->right;
        //to avoid the left most node ambiguity
        if ( p->right )
            p = p->right;
        else
            p = p->left;
    }
    while ( s.size() > 1 ) {
        std::cout << s.top()->val << ' ';
        s.pop();
    }
}

void print_edge_left( const Node * p, bool is_left_edge ) {

    if ( ! p ) return;
    
    if ( is_left_edge
      || ( ! p->left && ! p->right ) )
        std::cout << p->val << ' ';

    print_edge_left( p->left, is_left_edge );//must use is_left_edge!!!
    print_edge_left( p->right, is_left_edge && ( p->left ? false : true ) );//tricky!!!
}

void print_edge_right( const Node * p, bool is_right_edge ) {
    
    if ( ! p ) return;
    
    print_edge_right( p->left, is_right_edge && ( p->right ? false : true ) );
    print_edge_right( p->right, is_right_edge );
    if ( is_right_edge
      || ( ! p->left && ! p->right ) )
        std::cout << p->val << ' ';
}

void print_edge_recursive( const Node * root ) {
    
    if ( ! root ) return;

    std::cout << root->val << ' ';
    print_edge_left( root->left, true );
    print_edge_right( root->right, true );
}

int main() {

    {
        /**
         *     _30_
         *    /    \
         *   10    20
         *   /    /  \
         *  50   45  35
         */
        Node n1( 30 );
        Node n2( 10 );
        Node n3( 20 );
        Node n4( 50 );
        Node n5( 45 );
        Node n6( 35 );
        n1.left  = &n2;
        n1.right = &n3;
        n2.left  = &n4;
        n3.left  = &n5;
        n3.right = &n6;

        print_edge_iterative( &n1 );
        std::cout << std::endl;
        print_edge_recursive( &n1 );
        std::cout << std::endl;
    }

    {
        /*
        ______30______
       /              \
    __20__          __40__
   /      \        /      \
  10      25      35      50
 /  \       \            /
 5  15      28          41
        */

        Node n1( 30 );
        Node n2( 20 );
        Node n3( 40 );
        Node n4( 10 );
        Node n5( 25 );
        Node n6( 35 );
        Node n7( 50 );
        Node n8( 5  );
        Node n9( 15 );
        Node n10( 28 );
        Node n11( 41 );
        
        n1.left  = &n2;
        n1.right = &n3;
        n2.left  = &n4;
        n2.right = &n5;
        n3.left  = &n6;
        n3.right = &n7;
        n4.left  = &n8;
        n4.right = &n9;
        n5.right = &n10;
        n7.left  = &n11;

        print_edge_iterative( &n1 );
        std::cout << std::endl;
        print_edge_recursive( &n1 );
        std::cout << std::endl;
    }

    {
        /*
        ______1______
       /             \
    __2__           __3__
   /     \         /     \
  4       5       6       7
 /  \    / \     / \     / \
8    9  10  11  12  13  14  15
        */

        Node n1( 1 );
        Node n2( 2 );
        Node n3( 3 );
        Node n4( 4 );
        Node n5( 5 );
        Node n6( 6 );
        Node n7( 7 );
        Node n8( 8  );
        Node n9( 9 );
        Node n10( 10 );
        Node n11( 11 );
        Node n12( 12 );
        Node n13( 13 );
        Node n14( 14 );
        Node n15( 15 );
        
        n1.left  = &n2;
        n1.right = &n3;
        n2.left  = &n4;
        n2.right = &n5;
        n3.left  = &n6;
        n3.right = &n7;
        n4.left  = &n8;
        n4.right = &n9;
        n5.left  = &n10;
        n5.right = &n11;
        n6.left  = &n12;
        n6.right = &n13;
        n7.left  = &n14;
        n7.right = &n15;

        print_edge_iterative( &n1 );
        std::cout << std::endl;
        print_edge_recursive( &n1 );
        std::cout << std::endl;
    }

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
        
        print_edge_iterative( &n1 );
        std::cout << std::endl;
        print_edge_recursive( &n1 );
        std::cout << std::endl;

    }

    {
        /*
   _______________28_______________
  /                                \
  4___                         ____69
      \                       /
    ___8__                 __56__
   /      \               /      \
   7    __12___        __34    __27__
       /       \      /       /      \
      5_      _13    _2      _3      39
        \    /      /       /
         6  11     10       9
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
        n7.left  = &n10;
        n7.right = &n11;
        n8.left  = &n12;
        n9.left  = &n13;
        n9.right = &n14;
        n10.right = &n15;
        n11.left  = &n16;
        n12.left  = &n17;
        n13.left  = &n18;
        
        print_edge_iterative( &n1 );
        std::cout << std::endl;
        print_edge_recursive( &n1 );
        std::cout << std::endl;
    }
}

/**
(1)print root
(2)BFS the tree
(2.1) print the 1st node of each level (they are the left most nodes), and push the last node into a stack(they are the right most nodes)
(2.2) print the every node of the last level
(3) pop from the stack and print (they are the right most nodes)
*/


