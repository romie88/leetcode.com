/**
 * http://leetcode.com/2012/05/clone-graph-part-i.html
 * Clone Graph Part I
 *
 * May 30, 2012 Uncategorized
 *
 * Clone a graph. Input is a Node pointer. Return the Node pointer of the
 * cloned graph.
 *
 * A graph is defined below:
 * struct Node {
 * vector neighbors;
 * }
 */

/**
 * First question this graph is directed or undirected.
 *
 * We think it is directed since the representation indicates so.
 *
 * Second to clone an graph we need to traverse the graph by either
 * bfs or dfs. But we need to be careful with the loop in the graph.
 */

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <iostream>

struct Node {
    int val;
    std::vector< Node * > neighbors;
    Node( int v ) : val( v ) {}
};

//clone a graph using bfs
Node * clone_graph_bfs( Node * p ) {
    
    if ( ! p ) return nullptr;

    std::unordered_map< Node *, Node * > map;
    Node * p_copy = new Node( p->val );
    map.insert( std::pair< Node *, Node * >( p, p_copy ) );
    
    std::queue< Node * > q;
    q.push( p );
    while ( ! q.empty() ) {

        Node * t = q.front();
        q.pop();

        for ( const auto n : t->neighbors ) {
            Node * n_copy = nullptr;
            const auto & it = map.find( n );
            if ( it == map.end() ) {
                n_copy = new Node( n->val );
                map.insert( std::pair< Node *, Node * >( n, n_copy ) );
                q.push( n );
            } else {
                n_copy = it->second;
            }
            map[ t ]->neighbors.push_back( n_copy );
        }
    }

    return p_copy;
}

//clone a graph using dfs recursive
Node * clone_graph_dfs_impl(
        Node * p,
        std::unordered_map< Node *, Node * > & map ) {
    
    if ( ! p ) return nullptr;
    
    Node * p_copy = nullptr;
    const auto & it = map.find( p );
    if ( it == map.end() ) {
        p_copy = new Node( p->val );
        map.insert( std::pair< Node *, Node * >( p, p_copy ) );
    } else {
        return it->second;
    }
    
    for ( const auto t : p->neighbors ) {
        Node * t_copy = clone_graph_dfs_impl( t, map );
        p_copy->neighbors.push_back( t_copy );
    }

    return p_copy;
}

Node * clone_graph_dfs( Node * p ) {

    std::unordered_map< Node *, Node * > map;
    return clone_graph_dfs_impl( p, map );
}

//print graph using dfs recursive
void print_graph_dfs_recursive_impl(
        Node * p,
        std::unordered_set< Node * > & s ) {
    
    if ( ! p ) return;
    
    if ( s.find( p ) != s.end() )
        return;

    std::cout << p->val << " ";
    s.insert( p );
    
    for ( const auto t : p->neighbors )
        print_graph_dfs_recursive_impl( t, s );
}

void print_graph_dfs_recursive( Node * p ) {

    std::unordered_set< Node * > s;
    print_graph_dfs_recursive_impl( p, s );
    std::cout << std::endl;
}

int main() {

    Node n1( 1 );
    Node n2( 2 );
    Node n3( 3 );
    Node n4( 4 );
    n1.neighbors.push_back( &n2 );
    n1.neighbors.push_back( &n3 );
    n2.neighbors.push_back( &n3 );
    n3.neighbors.push_back( &n4 );
    
    //print the graph
    print_graph_dfs_recursive( &n1 );
    
    //bfs clone
    Node * p_bfs = clone_graph_bfs( &n1 );
    //print bfs cloned graph
    print_graph_dfs_recursive( p_bfs );
    
    //dfs clone
    Node * p_dfs = clone_graph_dfs( &n1 );
    //print dfs cloned graph
    print_graph_dfs_recursive( p_dfs );
    
    return 0;
}

