/**
 * http://leetcode.com/2011/05/a-distance-maximizing-problem.html
 * A Distance Maximizing Problem
 *
 * 2011-05-19 Uncategorized
 *
 * Given an array A of integers, find the maximum of j-i subjected to the
 * constraint of A[i] < A[j].
 */

/**
 * Hint:
This problem seemed easy, maybe because it is easy to understand. But is it straightforward to solve? If you are thinking of a straightforward solution, think again. Try to come up with a solution with run time complexity of O(n log n). Can you do better than that?

Solution:

Visualization of the problem using n vertical lines. The ith line’s height is represented by A[i], assuming A[i] is positive.

We are able to visualize the above problem better by drawing n vertical lines, where the height of ith line corresponds to the ith element in A. We first assume that all elements in A are positive integers, but later it can be expanded to non-positive integers as well. Now, unless the elements in A forms a strictly non-increasing order, there must exist a pair of (i, j) such that A[i] < A[j], and i < j. Therefore, the above problem is equivalent of finding the maximum distance between two vertical lines, where the left line must be shorter than the right line.

Brute Force O(N2)
The straightforward brute force way is to find the shortest line (the starting index, i), then try to look toward the right side (the ending index, j) and find a taller line with the furthest distance. Record the distance (j-i)and repeat with the next shortest line. Clearly, this is an O(N2) algorithm and we can do better.

Sorting O(N log N)

Above diagram shows n lines sorted according its heights. Lines with same heights are sorted using its original index. We will also need to keep track of each line’s original index in order to calculate the distance later. Finally, we build a table by scanning the lines’ original index from right to left once.

By sorting the lines according to its height, we can achieve better run time complexity. Notice that once we sorted the lines, we are able to find the maximum distance in O(N) time. For each possible original starting index i, we find the original ending index j, which is the maximum among all j’s where A[j] > A[i]. To enable the quick search for the maximum, we can build a look up table in O(N) time by scanning from right to left once. For example, we start with index i = 4, which is the shortest line. We know the maximum of all original indices to the right is 7, therefore max distance = 7 – 4 = 3. For the next line which original index is 3, the max distance = 7 – 3 = 4. Now, we must skip over the duplicates and reach the line with its original index 1. Here, we must be careful to skip over all duplicate heights which are not part of the solution because not satisfying the constraint A[j] > A[i]. Therefore, the max distance for this case = 2 – 1 = 1.

Best Solution O(N)

Given two indices a and b, where would you rather choose as a potential starting point?

Credits for the best O(N) solution goes to darksteel, which I first learned this neat method from him. Anonymous is the only reader who is able to solve this correctly using the same idea, great job!

Solving this problem efficiently requires some clever observations to eliminate all unnecessary comparisons. It is non obvious to me at first if there exists an O(N) algorithm for this problem.

Please look at the above diagram carefully, and ask yourself if you would choose index a or b as a potential starting point. Clearly, you would never choose index b as the starting point. Why?

Assume that choosing index b as the starting point, the max distance is j-b, where A[j] > A[b]. Now, since a < b and A[a] is not taller than A[b] which implies that A[j] > A[a], we can form a farther distance by choosing a as the starting index. Therefore, we cannot choose b as the starting point as this forms a contradiction.

Generally, we want to choose only starting points with no such lines that are shorter to its left side. From the diagram above, only lines of index 0, 1, 3, 4 are valid starting points.

Once we gather all valid starting points by scanning once from left to right, we are able to obtain the maximum distance by scanning backwards.

It is obvious that if the ending point is less than the shortest starting point, then it won’t be a valid solution for all other starting points. Therefore, we scan from right to left until we meet the first ending point that satisfies the condition. Then, we proceed to the next shortest starting point, and continue on from the previous ending point. Using this strategy, we would guarantee that we are able to find the maximum distance in O(N) running time.

To be continued…
 */

/**
 * http://www.geeksforgeeks.org/given-an-array-arr-find-the-maximum-j-i-such-that-arrj-arri/
 *
 * http://www.geeksforgeeks.org/maximum-difference-between-two-elements/
 */

#include <iostream>
#include <algorithm>
#include <vector>

int max_dist_brute_force( int * a, int n, int & ii, int & jj ) {
    
    int max_dist = 0;
    for ( int i = 0; i < n - 1; ++i ) {
        for( int j = i + 1; j < n; ++j ) {
            if ( a[ i ] < a[ j ] ) {
                if ( j - i > max_dist ) {
                    max_dist = j - i;
                    ii = i;
                    jj = j;
                }
            }
        }
    }

    return max_dist;
}

#if 0
int max_dist_by_sorting( int * a, int n, int & ii, int & jj ) {

    struct Element {
        int val;
        int index;
        Element( int v, int i ) : val( v ), index( i ) {}
    };

    struct ElementComp {
        bool operator()( const Element & e1, const Element & e2 ) const {
            if ( e1.val < e2.val ) return true;
            else if ( e1.val == e2.val ) return e1.index < e2.index;
            else return false;
        }
    };
    
    std::vector< Element > v;
    for ( int i = 0; i < n; ++i )
        v.push_back( Element( a[ i ], i ) );
    
    std::sort( v.begin(), v.end(), ElementComp() );
    
    int max_dist = 0;
    int index_j = v[ v.size() - 1 ].index;
    for ( int k = v.size() - 2; k >= 0; --k ) {
        
        if ( v[ k ].index > index_j ) {
            index_j = v[ k ].index;
        }
        
        if ( index_j - v[ k ].index > max_dist
          && a[ index_j ] > a[ v[ k ].index ]/* handle duplicates */ ) {
            ii = v[ k ].index;
            jj = index_j;
            max_dist = jj - ii;
        }
    }

    return max_dist;
}
#endif

int max_dist_efficient( int * a, int n, int & ii, int & jj ) {
    
    std::vector< int > lmin( n );//lmin[ i ] constains the min from a[ 0 ] to a[ i ]
    std::vector< int > rmax( n );//rmax[ i ] constains the max from a[ i ] to a[ n - 1 ]

    lmin[ 0 ] = a[ 0 ];
    for ( int i = 1; i < n; ++i )
        lmin[ i ] = std::min( a[ i ], lmin[ i - 1 ] );

    rmax[ n - 1 ] = a[ n - 1 ];
    for ( int j = n - 2; j >= 0; --j )
        rmax[ j ] = std::max( a[ j ], rmax[ j + 1 ] ); 

    int max_dist = 0;
    for ( int i = 0, j = 0; i < n && j < n; ) {
        if ( lmin[ i ] < rmax[ j ] ) {
            max_dist = std::max( max_dist, j - i );
            ii = i;
            jj = j;
            ++j;
        } else {
            ++i;
        }
    }

    return max_dist;
}

int main() {

    int a1[] = { 4, 3, 5, 2, 1, 3, 2, 3 };
    int a2[] = { 34, 8, 10, 3, 2, 80, 30, 33, 1 };
    int a3[] = { 9, 2, 3, 4, 5, 6, 7, 8, 18, 0 };
    int a4[] = { 1, 2, 3, 4, 5, 6 };
    int a5[] = { 6, 5, 4, 3, 2, 1 };
    int a6[] = { 3, 4, 5, 3, 3 };

/*
4 i = 3 j = 7
6 i = 1 j = 7
8 i = 0 j = 8
5 i = 0 j = 5
0 i = 0 j = 5
2 i = 0 j = 2
*/

    int i = -1, j = -1;
    int max_dist = 0;

    max_dist = max_dist_efficient( a1, sizeof( a1 ) / sizeof( a1[ 0 ] ), i, j );
    std::cout << max_dist << " i = " << i << " j = " << j << std::endl;

    max_dist = max_dist_efficient( a2, sizeof( a2 ) / sizeof( a2[ 0 ] ), i, j );
    std::cout << max_dist << " i = " << i << " j = " << j << std::endl;

    max_dist = max_dist_efficient( a3, sizeof( a3 ) / sizeof( a3[ 0 ] ), i, j );
    std::cout << max_dist << " i = " << i << " j = " << j << std::endl;

    max_dist = max_dist_efficient( a4, sizeof( a4 ) / sizeof( a4[ 0 ] ), i, j );
    std::cout << max_dist << " i = " << i << " j = " << j << std::endl;

    max_dist = max_dist_efficient( a5, sizeof( a5 ) / sizeof( a5[ 0 ] ), i, j );
    std::cout << max_dist << " i = " << i << " j = " << j << std::endl;

    max_dist = max_dist_efficient( a6, sizeof( a6 ) / sizeof( a6[ 0 ] ), i, j );
    std::cout << max_dist << " i = " << i << " j = " << j << std::endl;

    return 0;
}
