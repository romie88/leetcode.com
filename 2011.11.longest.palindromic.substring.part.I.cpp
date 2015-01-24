/**
 * http://leetcode.com/2011/11/longest-palindromic-substring-part-i.html
 * Longest Palindromic Substring Part I
 *
 * November 20, 2011 in dynamic programming, string
 *
 * Given a string S, find the longest palindromic substring in S.
 */

#include <iostream>
#include <string>
#include <vector>

bool is_palindrome( const std::string & s,
                    std::string::size_type i,
                    std::string::size_type j ) {
    while ( i < j ) {
        if ( s[ i ] != s[ j ] )
            return false;
        ++i;
        --j;
    }
    return true;
}

//the time complexity of brute force method is O(N^3)
void longest_palindromic_substring_brute_force(
        const std::string & s,
        std::string::size_type & len,
        std::vector< std::string::size_type > & start_index_vec ) {
    
    const std::string::size_type s_len = s.length();
    start_index_vec.clear();
    
    if ( s_len == 0 ) {
        len = 0;
        return;
    }

    //brute force
    //check all the substrings from s with length >= 2 one by one
    //a substring with length 1 is a palindrome for sure
    len = 1;
    for ( std::string::size_type i = 0; i < s_len; ++i ) {
        for ( std::string::size_type j = i + 1; j < s_len; ++j ) {
            if ( is_palindrome( s, i, j ) && j - i + 1 > len )
                len = j - i + 1;
        }
    }
    
    //now we know the length of the longest palindromic substring
    //we are going to search and save the starting index of them
    for ( std::string::size_type i = 0; i + len <= s_len; ++i ) {
        if ( is_palindrome( s, i, i + len - 1 ) )
            start_index_vec.push_back( i );
    }
}

//time complexity O(N^2)
//space complexity O(N^2)
void longest_palindromic_substring_dp(
        const std::string & s,
        std::string::size_type & len,
        std::vector< std::string::size_type > & start_index_vec ) {
    
    const std::string::size_type s_len = s.length();
    start_index_vec.clear();
    
    if ( s_len == 0 ) {
        len = 0;
        return;
    }

    //p matrix
    //p[ i ][ j ] == true iff the substring s[ i ] ... s[ j ] is a palindrome
    std::vector< std::vector< bool > > p( s_len, std::vector< bool >( s_len, false ) );
    
    //base case one: p[ i ][ i ] = true
    //all the single alphabet is a palindrome
    len = 1;
    for ( std::vector< std::vector< bool > >::size_type i = 0; i < p.size(); ++i )
        p[ i ][ i ] = true;
    
    //base case two: p[ i ][ i + 1 ] == true iff s[ i ] == s[ i + 1 ] for i = 0, ..., len - 2
    for ( std::vector< std::vector< bool > >::size_type i = 0; i < p.size() - 1; ++i ) {
        p[ i ][ i + 1 ] = ( s[ i ] == s[ i + 1 ] );
        if ( s[ i ] == s[ i + 1 ] )
            len = 2;
    }
    
    //recurrence relation
    //p[ i ][ j ] == true iff p[ i - 1 ][ j - 1 ] == true && s[ i ] == s[ j ]
    for ( std::vector< std::vector< int > >::size_type offset = 2;
          offset < s_len; ++offset ) {
        for ( std::vector< std::vector< bool > >::size_type i = 0;
              i < s_len - offset; ++i ) {
            p[ i ][ i + offset ] = ( p[ i + 1 ][ i + offset - 1 ] && s[ i ] == s[ i + offset ] );
            if ( p[ i ][ i + offset ] && offset + 1 > len )
                len = offset + 1;
        }
    }

    //with len we can search through p matrix to get all the starting index
    //of the longest palindromic substrings
    for ( std::vector< std::vector< bool > >::size_type i = 0;
          i + len <= s_len; ++i ) {
        if ( p[ i ][ i + len - 1 ] )
            start_index_vec.push_back( i );
    }
}

//time complexity O(N^2)
//space complexity O(1)
void expand_around_center(
        const std::string & s,
        int & cl,
        int & cr ) {
    
    const std::string::size_type s_len = s.length();

    while ( cl >= 0 && cr < s_len && s[ cl ] == s[ cr ] ) {
        --cl;
        ++cr;
    }
    ++cl;
    --cr;
}

void longest_palindromic_substring_center(
        const std::string & s, 
        std::string::size_type & len,
        std::vector< std::string::size_type > & start_index_vec ) {
    
    const std::string::size_type s_len = s.length();
    start_index_vec.clear();
    
    if ( s_len == 0 ) {
        len = 0;
        return;
    }
    
    len = 0;
    for ( std::string::size_type i = 0; i < s_len; ++i ) {
        
        int cl, cr;

        //expand around center s[ i ]
        cl = i; cr = i;
        expand_around_center( s, cl, cr );
        if ( cr - cl + 1 > len ) {
            len = cr - cl + 1;
            start_index_vec.clear();
            start_index_vec.push_back( cl );
        } else if ( cr - cl + 1 == len ) {
            start_index_vec.push_back( cl );
        }

        //expand around center s[ i ] and s[ i + 1 ]
        cl = i; cr = i + 1;
        if ( i + 1 < s_len ) {
            expand_around_center( s, cl, cr );
            if ( cr - cl + 1 > len ) {
                len = cr - cl + 1;
                start_index_vec.clear();
                start_index_vec.push_back( cl );
            } else if ( cr - cl + 1 == len ) {
                start_index_vec.push_back( cl );
            }
        }
    }
}

int main() {
    
    std::string s;
    std::cout << "please enter a string: ";
    std::cin >> s;
    
    std::string::size_type len1;
    std::vector< std::string::size_type > start_index_vec1;

    longest_palindromic_substring_brute_force( s, len1, start_index_vec1 );

    std::cout << len1 << std::endl;
    for ( const auto i : start_index_vec1 ) {
        std::cout << i << " " << s.substr( i, len1 ) << std::endl;
    }

    std::string::size_type len2;
    std::vector< std::string::size_type > start_index_vec2;
    longest_palindromic_substring_dp( s, len2, start_index_vec2 );

    std::cout << len2 << std::endl;
    for ( const auto i : start_index_vec2 ) {
        std::cout << i << " " << s.substr( i, len2 ) << std::endl;
    }

    std::string::size_type len3;
    std::vector< std::string::size_type > start_index_vec3;
    longest_palindromic_substring_center( s, len3, start_index_vec3 );

    std::cout << len3 << std::endl;
    for ( const auto i : start_index_vec3 ) {
        std::cout << i << " " << s.substr( i, len3 ) << std::endl;
    }
    
    return 0;
}

