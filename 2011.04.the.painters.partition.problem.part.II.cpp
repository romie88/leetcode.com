/**
 * http://leetcode.com/2011/04/the-painters-partition-problem-part-ii.html
 * The Painter’s Partition Problem Part II
 *
 * April 6, 2011 in binary search
 *
 * You have to paint N boards of length {A0, A1, A2 … AN-1}. There are K
 * painters available and you are also given how much time a painter takes to
 * paint 1 unit of board. You have to get this job done as soon as possible
 * under the constraints that any painter will only paint continuous sections
 * of board, say board {2, 3, 4} or only board {1} or nothing but not board
 * {2, 4, 5}.
 */

#include <iostream>

int num_partition( int * a, int n, int cost ) {
    
    int c = 0;
    int p = 0;
    for ( int i = 0; i < n; ++i ) {
        
        if ( c + a[ i ] > cost ) {
            ++p;
            c = a[ i ];
        } else {
            c += a[ i ];
        }
    }
    ++p;

    return p;
}

int best_partition_by_binary_search( int * a, int n, int k ) {
    
    int low = a[ 0 ];
    int high = 0;
    for ( int i = 0; i < n; ++i ) {
        high += a[ i ];
        if ( a[ i ] > low )
            low = a[ i ];
    }
    
    int mid = ( low + high ) / 2;
    while ( low < high ) {
        
        mid = ( low + high ) / 2;
        int x = num_partition( a, n, mid );

        std::cout << "low = "<< low << " high = " << high << " mid = " << mid << " x = " << x << std::endl;
        if ( x <= k ) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }

    return mid;
}

int main() {

    int a[] = { 100, 200, 300, 400, 500, 600, 700, 800, 900 };

    std::cout << best_partition_by_binary_search( a, sizeof( a ) / sizeof( a[ 0 ] ), 3 ) << std::endl;

    return 0;
}
