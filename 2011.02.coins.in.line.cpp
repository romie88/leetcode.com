/**
 * http://leetcode.com/2011/02/coins-in-line.html
 * Coins in a Line
 *
 * February 9, 2011 in dynamic programming
 *
 * There are n coins in a line. (Assume n is even).
 * Two players take turns to take a coin from one of the ends of the line
 * until there are no more coins left. The player with the larger amount
 * of money wins.
 * 
 * Would you rather go first or second? Does it matter?
 * Assume that you go first, describe an algorithm to compute the maximum
 * amount of money you can win.
 */

#include <iostream>
#include <vector>
#include <algorithm>

/**
 * Assume you go first and your opponent is as smart as you.
 */
int max_money_smart_opponent_dp( int * c, int n, std::vector< int > & moves ) {
    
    //dp table
    //index starts from 1
    //p( i, j ) denotes the optimal value you can get when it's your turn
    //and the coins left are c_i, ..., c_j.
    std::vector< std::vector< int > > p( n + 1, std::vector< int >( n + 1, 0 ) );
    
    //initialize base cases
    for ( int i = 1; i <= n; ++i )
        p[ i ][ i ] = c[ i - 1 ];

    //calculate p matrix in a bottom-up fashion
    for ( int k = n - 1; k >= 1; --k ) {
        int sum_c = c[ k - 1 ];
        for ( int t = k + 1; t <= n; ++t ) {
            sum_c += c[ t - 1 ];
            p[ k ][ t ] = sum_c - std::min( p[ k ][ t - 1 ], p[ k + 1 ][ t ] );
        }
    }
    
    int i = 1, j = n;
    while ( i <= j ) {
        if ( p[ i ][ j - 1 ] >= p[ i + 1 ][ j ] ) {
            moves.push_back( i );
            ++i;
        } else {
            moves.push_back( j );
            --j;
        }
    }
    
    for ( const auto & r : p ) {
        for ( const auto & c : r ) {
            std::cout << c << " ";
        }
        std::cout << std::endl;
    }

    return p[ 1 ][ n ];
}

/**
 * Assume you go first and your opponet is as smart as you.
 * An improved version of dp without the calculation of summation of c_i
 */
int max_money_smart_opponent_dp_2( int * c, int n, std::vector< int > & moves ) {
    
    //dp table
    //index starts from 1
    //p( i, j ) denotes the optimal value you can get when it's your turn
    //and the coins left are c_i, ..., c_j.
    std::vector< std::vector< int > > p( n + 1, std::vector< int >( n + 1, 0 ) );
    
    for ( int i = 1; i <= n; ++i )
        p[ i ][ i ] = c[ i - 1 ];

    for ( int i = 2; i <= n; ++i ) {
        for ( int k = 1, t = i; t <= n; ++k, ++t ) {

            int a = k + 2 <= n ? p[ k + 2 ][ t ] : 0;
            int b = k + 1 <= n && t - 1 >= 1 ? p[ k + 1 ][ t - 1 ] : 0;
            int x = t - 2 >= 1 ? p[ k ][ t - 2 ] : 0;

            p[ k ][ t ] = std::max( c[ k - 1 ] + std::min( a, b ),
                                    c[ t - 1 ] + std::min( b, x ) );
        }
    }
    
    int i = 1, j = n;
    while ( i <= j ) {
        if ( p[ i ][ j - 1 ] >= p[ i + 1 ][ j ] ) {
            moves.push_back( i );
            ++i;
        } else {
            moves.push_back( j );
            --j;
        }
    }

    for ( const auto & r : p ) {
        for ( const auto & c : r ) {
            std::cout << c << " ";
        }
        std::cout << std::endl;
    }
    
    return p[ 1 ][ n ];
}



int main() {

    {
    int c[] = { 3, 2, 2, 3, 1, 2 };
    std::vector< int > moves;
    std::cout << max_money_smart_opponent_dp( c, 
                                              sizeof( c ) / sizeof( c[ 0 ] ),
                                              moves )
              << std::endl;
    
    std::cout << "moves: " << std::endl;
    for ( const auto & m : moves )
        std::cout << m << std::endl;

    std::cout << std::endl;
    }

    {
    int c[] = { 3, 2, 2, 3, 1, 2 };
    std::vector< int > moves;
    std::cout << max_money_smart_opponent_dp_2( c, 
                                                sizeof( c ) / sizeof( c[ 0 ] ),
                                                moves )
              << std::endl;
    
    std::cout << "moves: " << std::endl;
    for ( const auto & m : moves )
        std::cout << m << std::endl;
    }

    return 0;
}

