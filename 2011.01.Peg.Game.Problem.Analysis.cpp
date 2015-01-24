/**
 * http://leetcode.com/2011/01/peg-game-problem-analysis.html
 * Peg Game Problem Analysis
 *
 * January 10, 2011 in Uncategorized
 *
 * At the arcade, you can play a simple game where a ball is dropped into the top of the game, from a position of your choosing. There are a number of pegs that the ball will bounce off of as it drops through the game. Whenever the ball hits a peg, it will bounce to the left with probability 0.5 and to the right with probability 0.5. The one exception to this is when it hits a peg on the far left or right side, in which case it always bounces towards the middle.

When the game was first made, the pegs where arranged in a regular grid. However, it’s an old game, and now some of the pegs are missing. Your goal in the game is to get the ball to fall out of the bottom of the game in a specific location. Your task is, given the arrangement of the game, to determine the optimal place to drop the ball, such that the probability of getting it to this specific location is maximized.

The image below shows an example of a game with five rows of five columns. Notice that the top row has five pegs, the next row has four pegs, the next five, and so on. With five columns, there are four choices to drop the ball into (indexed from 0). Note that in this example, there are three pegs missing. The top row is row 0, and the leftmost peg is column 0, so the coordinates of the missing pegs are (1,1), (2,1) and (3,2). In this example, the best place to drop the ball is on the far left, in column 0, which gives a 50% chance that it will end in the goal.

x.x.x.x.x
 x...x.x
x...x.x.x
 x.x...x
x.x.x.x.x
 G
‘x’ indicates a peg, ‘.’ indicates empty space.

Input
You should first read an integer N, the number of test cases. Each of the next N lines will then contain a single test case. Each test case will start with integers R and C, the number of rows and columns (R will be odd). Next, an integer K will specify the target column. Finally, an integer M will be followed by M pairs of integer ri and ci, giving the locations of the missing pegs.

Constraints
1 = N = 100
3 = R,C = 100

The top and bottom rows will not have any missing pegs.
Other parameters will all be valid, given R and C

Output
For each test case, you should output an integer, the location to drop the ball into, followed by the probability that the ball will end in columns K, formatted with exactly six digits after the decimal point (round the last digit, don’t truncate).

Notes
The input will be designed such that minor rounding errors will not impact the output (i.e. there will be no ties or near — up to 1E-9 — ties, and the direction of rounding for the output will not be impacted by small errors).
*/

#include <vector>
#include <utility>
#include <unordered_set>
#include <iostream>
#include <functional>
#include <sstream>

namespace std {

template <> struct hash< std::pair< int, int > > {

    std::size_t operator()( const std::pair< int, int > & p ) const {

        std::ostringstream oss;
        oss << p.first << "," << p.second;
        
        std::hash< std::string > hash_fn;
        return hash_fn( oss.str() );
    }

};

}

void get_max_probability( const int R,
                          const int C,
                          const int K,
                          const std::vector< std::pair< int, int > > & missing_pegs_loc,
                          int & D,
                          double & max_p ) {
    //R must be odd
    
    //convert vector input into unordered_set
    std::unordered_set< std::pair< int, int > > missing_pegs_set;
    for ( const auto & loc : missing_pegs_loc )
        missing_pegs_set.insert( loc );
    
    std::vector< std::vector< double > >
        p( R, std::vector< double >( C - 1, 0.0 ) );

    //initialize the last row
    for ( int i = 0; i < C - 1; ++i ) {
        if ( i == K )
            p[ R - 1 ][ i ] = 1.0;
    }

    //calculate p matrix bottom-up
    for ( int i = R - 2; i >= 0; --i ) {
        
        //index is odd then we have C - 2 columns
        if ( i % 2 == 1 ) { 
            
            for ( int j = 0; j < C - 2; ++j ) {
                
                //there is a peg under index j
                if ( missing_pegs_set.find( std::pair< int, int >( i + 1, j + 1 ) )
                  == missing_pegs_set.end() ) {
                    p[ i ][ j ] = 0.5 * p[ i + 1 ][ j ] + 0.5 * p[ i + 1 ][ j + 1 ];
                } else {
                //there is no peg under index j
                    p[ i ][ j ] = p[ i + 2 ][ j ];
                }
            }
        } else {
        //index is even then we have C - 1 columns
        
            for ( int j = 0; j < C - 1; ++j ) {

                //there is a peg under index j
                if ( missing_pegs_set.find( std::pair< int, int >( i + 1, j ) )
                  == missing_pegs_set.end() ) {
                    //boundary pegs
                    if ( j == 0  ) {
                        p[ i ][ j ] = p[ i + 1 ][ j ];
                    } else if ( j == C - 2 ) {
                        p[ i ][ j ] = p[ i + 1 ][ j - 1 ];
                    } else {
                        p[ i ][ j ] = 0.5 * p[ i + 1 ][ j - 1 ] + 0.5 * p[ i + 1 ][ j ];
                    }
                } else {
                //there is no peg under index j
                    p[ i ][ j ] = p[ i + 2 ][ j ];
                }
            }
        }
    }

    for ( const auto & r : p ) {
        for ( const auto & c : r ) {
            std::cout << c << " ";
        }
        std::cout << std::endl;
    }

    D = 0;
    max_p = p[ 0 ][ D ];
    for ( int j = 1; j < C - 1; ++j ) {
        if ( p[ 0 ][ j ] > max_p ) {
            D = j;
            max_p = p[ 0 ][ j ];
        }
    }
}

int main() {

    int R = 5;
    int C = 5;
    int K = 0;
    std::vector< std::pair< int, int > > missing_pegs_loc;
    missing_pegs_loc.push_back( std::make_pair( 1, 1 ) );
    missing_pegs_loc.push_back( std::make_pair( 2, 1 ) );
    missing_pegs_loc.push_back( std::make_pair( 3, 2 ) );
    int D;
    double max_p;
    get_max_probability( R, C, K, missing_pegs_loc, D, max_p );
    
    std::cout << "D = " << D << " max_p = " << max_p << std::endl;

    return 0;
}
