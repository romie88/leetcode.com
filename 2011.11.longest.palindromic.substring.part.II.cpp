/**
 * http://leetcode.com/2011/11/longest-palindromic-substring-part-ii.html
 * Longest Palindromic Substring Part II
 *
 * November 20, 2011 in string
 *
 * Given a string S, find the longest palindromic substring in S.
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

void preprocess( const std::string & s,
                 std::string & t ) {

    t.push_back( '^' );
    for ( const auto c : s ) {
        t.push_back( '#' );
        t.push_back( c );
    }
    if ( ! s.empty() )
        t.push_back( '#' );
    t.push_back( '$' );
}

//Manacher's Algorithm
//time complexity O(N)
//space complexity O(N)
void longest_palindromic_substring_manacher(
        const std::string & s, 
        std::string::size_type & len,
        std::vector< std::string::size_type > & start_index_vec ) {
    
    const std::string::size_type s_len = s.length();
    start_index_vec.clear();
    
    if ( s_len == 0 ) {
        len = 0;
        return;
    }
    
    std::string t;
    preprocess( s, t );

    std::vector< int > p( t.length(), 0 );
    int C = 0;//Center
    int R = 0;//Right bound
    for ( std::string::size_type i = 1; i < t.length() - 1; ++i ) {
        
        //mirror of i against C
        int i2 = C - ( i - C );

        p[ i ] = R > i ? std::min< int >( R - i, p[ i2 ] ) : 0;
        
        //try to expand palindrome centered at i
        while ( t[ i + p[ i ] + 1 ] == t[ i - p[ i ] - 1 ] )
            ++p[ i ];

        //if palindrome centered at i expand past R
        //adjust center based on expanded palindrome
        if ( i + p[ i ] > R ) {
            C = i;
            R = i + p[ i ];
        }
    }

    //find the maximum element in p
    len = 0;
    for ( const auto i : p )
        if ( i > len )
            len = i;

    for ( std::vector< int >::size_type i = 0; i < p.size(); ++i )
        if ( p[ i ] == len ) {
            
            //map the start index of the palindrome in t back to s
            int start_in_t = i - len;
            start_in_t += start_in_t % 2;
            start_index_vec.push_back( ( start_in_t - 2 ) / 2 );
        }
}

int main() {
    
    std::string s;
    std::cout << "please enter a string: ";
    std::cin >> s;
    
    std::string::size_type len1;
    std::vector< std::string::size_type > start_index_vec1;

    longest_palindromic_substring_manacher( s, len1, start_index_vec1 );

    std::cout << len1 << std::endl;
    for ( const auto i : start_index_vec1 ) {
        std::cout << i << " " << s.substr( i, len1 ) << std::endl;
    }

    return 0;
}

