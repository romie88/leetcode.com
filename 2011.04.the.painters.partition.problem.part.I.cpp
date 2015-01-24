/**
 * http://leetcode.com/2011/04/the-painters-partition-problem.html
 * The Painter’s Partition Problem Part I
 *
 * April 5, 2011 in dynamic programming
 *
 * You have to paint N boards of length {A0, A1, A2 … AN-1}. There are K
 * painters available and you are also given how much time a painter takes to
 * paint 1 unit of board. You have to get this job done as soon as possible
 * under the constraints that any painter will only paint continuous sections
 * of board, say board {2, 3, 4} or only board {1} or nothing but not board
 * {2, 4, 5}.
 */

/**
 * Let M( n, k ) be the optimal value of the problem for n boards and k partitions.
 * M( n, k ) = min ( max ( sum( a[ i ] ), M( j, k - 1 ) ) )
 *          j = 1,,n     i=j,,n-1
 */

#include <iostream>
#include <algorithm>

int sum( int * a, int s, int e ) {

    int total = 0;
    for ( int i = s; i <= e; ++i )
        total += a[ i ];
    return total;

}

int best_partition_brute_force( int * a, int n, int k ) {
    
    if ( n == 1 ) return a[ 0 ];
    if ( k == 1 ) return sum( a, 0, n - 1 );
    
    //use j = 1 case to initialize min
    int sum_j = sum( a, 1, n - 1 );
    int min = std::max( best_partition_brute_force( a, 1, k - 1 ), sum_j );
    for ( int j = 2; j <= n; ++j ) {
        int val = std::max( best_partition_brute_force( a, j, k - 1 ), sum_j - a[ j - 1 ] );
        sum_j -= a[ j - 1 ];
        if ( val < min )
            min = val;
    }

    return min;
}

int best_partition_dp( int * a, int n, int k ) {
    
    //m[ i ][ j ] contains the solution to n = i and k = j
    //and m[ 0 ][ * ] and m[ * ][ 0 ] are not used
    //we make it to index easily starting from 1 instead of 0
    std::vector< std::vector< int > >
        m( n + 1, std::vector< int >( k + 1, 0 ) );
    
    //cum_sum[ i ] = a[ 0 ] + ... + a[ i - 1 ]
    //index starts from 1 instead of 0
    std::vector< int > cum_sum( n + 1, 0 );
    for ( int i = 1; i <= n; ++i )
        cum_sum[ i ] = cum_sum[ i - 1 ] + a[ i - 1 ];
    
    //initialize the base cases
    for ( int i = 1; i <= n; ++i )
        m[ i ][ 1 ] = cum_sum[ i ];
    for ( int j = 1; j <= k; ++j )
        m[ 1 ][ j ] = a[ 0 ];
    
    //dp in a bottom-up fashion
    for ( int i = 2; i <= n; ++i ) {
        for ( int j = 2; j <=k; ++j ) {
            //initialize optimal val
            int optimal_val = std::max( m[ 1 ][ j ], cum_sum[ i ] - cum_sum[ 1 ] );
            for ( int p = 2; p <= i; ++p ) {
                optimal_val = std::min( optimal_val,
                                        std::max( m[ p ][ j - 1 ], cum_sum[ i ] - cum_sum[ p ] ) );
            }
            m[ i ][ j ] = optimal_val;
        }
    }

    return m[ n ][ k ];
}

int main() {

    int a[] = { 100, 200, 300, 400, 500, 600, 700, 800, 900 };

    std::cout << best_partition_brute_force( a, sizeof( a ) / sizeof( a[ 0 ] ), 3 ) << std::endl;

    std::cout << best_partition_dp( a, sizeof( a ) / sizeof( a[ 0 ] ), 3 ) << std::endl;

    return 0;
}
