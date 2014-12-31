/**
 * http://leetcode.com/2011/05/determine-if-two-rectangles-overlap.html
 * Determine If Two Rectangles Overlap
 * 
 * May 12, 2011 in Uncategorized
 *
 * Given two axis-aligned rectangles A and B. Write a function to determine if
 * the two rectangles overlap.
 */

#include <algorithm>

struct Point {
    int x;
    int y;
    Point( int xx, int yy ) : x( xx ), y( yy ) {}
};

struct Rectangle {

    Point p1;
    Point p2;

    Rectangle( const Point & p, const Point & q )
        : p1( p ), p2( q ) {}
};

bool does_overlap( const Rectangle & r1, const Rectangle & r2 ) {
    
    return ! ( std::max( r1.p1.x, r1.p2.x ) < std::min( r2.p1.x, r2.p2.x )
            || std::min( r1.p1.x, r1.p2.x ) > std::max( r2.p1.x, r2.p2.x )
            || std::max( r1.p1.y, r1.p2.y ) < std::min( r2.p1.y, r2.p2.y )
            || std::min( r1.p1.y, r1.p2.y ) > std::max( r2.p1.x, r2.p2.y ) ); 

}

