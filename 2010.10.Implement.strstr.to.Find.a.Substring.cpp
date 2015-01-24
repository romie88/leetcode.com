/**
 * http://leetcode.com/2010/10/implement-strstr-to-find-substring-in.html
 * Implement strstr() to Find a Substring in a String
 *
 * October 14, 2010 in string
 *
 * Write C code to implement the strstr (Search for a substring) function.
 * Do not use any system library such as strlen.
 */

#include <cassert>
#include <vector>

/**
 * Naive implementation
 * Assume N = length of the string, M = length of the target
 * the time complexity is O( N * M )
 */
const char * strstr_naive( const char * str, const char * target ) {
    
    assert( str != nullptr );
    assert( target != nullptr );
    
    //if target points to an empty string, str is returned
    if ( ! *target ) return str;

    while ( * str ) {
        const char * s = str;
        const char * t = target;
        while ( *s && *t && *s == *t ) {
            ++s;
            ++t;
        }
        
        if ( ! *t )//this is the hard point for me!!!
            return str;
        
        ++str;
    }
    
    return nullptr;
}

/**
 * Improvement over naive implementation
 * the time complexity is O( M * N - M + 1 )
 */
const char * strstr_naive_better( const char * str, const char * target ) {
    
    assert( str != nullptr );
    assert( target != nullptr );

    //if target points to an empty string, str is returned
    if ( ! *target ) return str;

    const char * s = str;
    const char * t = target;
    while ( *s && *t ) {
        ++s;
        ++t;
    }
    //str is shorter than target
    if ( *t ) return nullptr;
    
    --s;//s points to the first character corresponding to the null character
        //from t; walk back one character
    while ( *s ) {
        const char * s2 = str;
        t = target;
        while ( *s2 && *t && *s2 == *t ) {
            ++s2;
            ++t;
        }
        
        if ( ! *t )
            return str;

        ++str;
        ++s;
    }

    return nullptr;
}

/**
 * KMP string matching implementation
 * the time complexity is as following
 * preprocessing O( M )
 * matching O( N )
 */
const char * strstr_KMP( const char * str, const char * target ) {

    assert( str != nullptr );
    assert( target != nullptr );

    //if target points to an empty string, str is returned
    if ( ! *target ) return str;
    
    //get the length of the target
    int m = 0;
    const char * t = target;
    while ( *t ) {
        ++m;
        ++t;
    }

    //preprocessing the target string
    //calculate the prefix function
    std::vector< int > pi;
    pi.push_back( 0 );//pi[ 0 ] is 0
    int q = 0;//number of characters matched
    for ( int i = 1; i < m; ++i ) {
        while ( q > 0 && target[ i ] != target[ q ] )
            q = pi[ q - 1 ];
        if ( target[ i ] == target[ q ] )
            ++q;
        pi[ i ] = q;
    }

    q = 0;
    while ( *str ) {
        while ( q > 0 && *str != target[ q ] )
            q = pi[ q - 1 ];
        if ( *str == target[ q ] )
            ++q;
        if ( q == m )
            return str - m + 1;
        
        ++str;
    }

    return nullptr;
}

int main() {
    
    {
    const char *str = "abc";
    const char *target = "abcd";

    assert( strstr_naive( str, target ) == nullptr );
    assert( strstr_naive_better( str, target ) == nullptr );
    assert( strstr_KMP( str, target ) == nullptr );
    }

    {
    const char *str = "abcdefg";
    const char *target = "deh";

    assert( strstr_naive( str, target ) == nullptr );
    assert( strstr_naive_better( str, target ) == nullptr );
    assert( strstr_KMP( str, target ) == nullptr );
    }

    {
    const char *str = "abcdefg";
    const char *target = "cde";

    assert( strstr_naive( str, target ) == str + 2 );
    assert( strstr_naive_better( str, target ) == str + 2 );
    assert( strstr_KMP( str, target ) == str + 2 );
    }
        
    return 0;
}

/**
 * Boyer-Moore algorithm
 * Rabin-Karp algorithm
 * Finite automaton algorithm
 */
