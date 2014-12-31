/**
 * http://leetcode.com/2011/05/longest-substring-without-repeating-characters.html
 * Longest Substring Without Repeating Characters
 *
 * May 16, 2011 in string
 *
 * Given a string, find the length of the longest substring without repeating
 * characters. For example, the longest substring without repeating letters
 * for “abcabcbb” is “abc”, which the length is 3. For “bbbbb” the longest
 * substring is “b”, with the length of 1.
 */

#include <unordered_set>
#include <iostream>

int longest_substring_without_repeating_characters(
        const char * s,
        int & ii,
        int & jj ) {
    
    std::unordered_set< char > set;
    
    int max_len = -1;
    int i = 0;
    int j = 0;
    while ( *( s + j ) != '\0' ) {
        
        auto it = set.find( *( s + j ) );
        if ( it == set.end() ) {
            set.insert( *( s + j ) );
            ++j;
            if ( j - i > max_len ) {
                max_len = j - i;
                ii = i;
                jj = j;
            }
        } else {//found repeated character
            
            //move i forwards
            while ( *( s + i ) != *( s + j ) ) {
                set.erase( set.find( *( s + i ) ) );
                ++i;
            }
            ++i;
            ++j;
        }
    }
    //dont forget this!!!
    if ( j - i > max_len ) {
        max_len = j - i;
        ii = i;
        jj = j;
    }
    
    return max_len;
}

int main() {
    
    const char * s1 = "abcabcbb";
    const char * s2 = "bbbbb";
    const char * s3 = "abcbacd";

    int max_len = -1;
    int i = -1, j = -1;

    max_len = longest_substring_without_repeating_characters( s1, i, j );
    std::cout << max_len << " i = " << i << " j = " << j << std::endl;

    max_len = longest_substring_without_repeating_characters( s2, i, j );
    std::cout << max_len << " i = " << i << " j = " << j << std::endl;

    max_len = longest_substring_without_repeating_characters( s3, i, j );
    std::cout << max_len << " i = " << i << " j = " << j << std::endl;

    return 0;
}

