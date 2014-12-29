/**
 * http://leetcode.com/2011/09/regular-expression-matching.html
 * Regular Expression Matching
 *
 * 2011-09-01 backtracking, string
 *
 * Implement regular expression matching with support for ‘.’ and ‘*’.
 *
 * ‘.’ Matches any single character.
 * ‘*’ Matches zero or more of the preceding element.
 * The matching should cover the entire input string (not partial).
 *
 * The function prototype should be:
 * bool isMatch(const char *s, const char *p)
 *
 * Some examples:
 * isMatch(“aa”,”a”) → false
 * isMatch(“aa”,”aa”) → true
 * isMatch(“aaa”,”aa”) → false
 * isMatch(“aa”, “a*”) → true
 * isMatch(“aa”, “.*”) → true
 * isMatch(“ab”, “.*”) → true
 * isMatch(“aab”, “c*a*b”) → true
 */

/**
 * Online Judge
 * This problem is available at Online Judge.
 *
 * Background:
It might seem deceptively easy even you know the general idea, but programming it correctly with all the details require careful thought.

Edit:
It seems that some readers are confused about why the regex pattern “.*” matches the string “ab”. “.*” means repeat the preceding element 0 or more times. Here, the “preceding” element is the dot character in the pattern, which can match any characters. Therefore, the regex pattern “.*” allows the dot to be repeated any number of times, which matches any string (even an empty string).

Hints:
Think carefully how you would do matching of ‘*’. Please note that ‘*’ in regular expression is different from wildcard matching, as we match the previous character 0 or more times. But, how many times? If you are stuck, recursion is your friend.

This problem is a tricky one. Due to the huge number of edge cases, many people would write lengthy code and have numerous bugs on their first try. Try your best getting your code correct first, then refactor mercilessly to as clean and concise as possible!

Solution:
This looks just like a straight forward string matching, isn’t it? Couldn’t we just match the pattern and the input string character by character? The question is, how to match a ‘*’?

A natural way is to use a greedy approach; that is, we attempt to match the previous character as many as we can. Does this work? Let us look at some examples.

s = “abbbc”, p = “ab*c”
Assume we have matched the first ‘a’ on both s and p. When we see “b*” in p, we skip all b’s in s. Since the last ‘c’ matches on both side, they both match.

s = “ac”, p = “ab*c”
After the first ‘a’, we see that there is no b’s to skip for “b*”. We match the last ‘c’ on both side and conclude that they both match.

It seems that being greedy is good. But how about this case?

s = “abbc”, p = “ab*bbc”
When we see “b*” in p, we would have skip all b’s in s. They both should match, but we have no more b’s to match. Therefore, the greedy approach fails in the above case.

One might be tempted to think of a quick workaround. How about counting the number of consecutive b’s in s? If it is smaller or equal to the number of consecutive b’s after “b*” in p, we conclude they both match and continue from there. For the opposite, we conclude there is not a match.

This seem to solve the above problem, but how about this case:
s = “abcbcd”, p = “a.*c.*d”

Here, “.*” in p means repeat ‘.’ 0 or more times. Since ‘.’ can match any character, it is not clear how many times ‘.’ should be repeated. Should the ‘c’ in p matches the first or second ‘c’ in s? Unfortunately, there is no way to tell without using some kind of exhaustive search.

We need some kind of backtracking mechanism such that when a matching fails, we return to the last successful matching state and attempt to match more characters in s with ‘*’. This approach leads naturally to recursion.

The recursion mainly breaks down elegantly to the following two cases:

If the next character of p is NOT ‘*’, then it must match the current character of s. Continue pattern matching with the next character of both s and p.
If the next character of p is ‘*’, then we do a brute force exhaustive matching of 0, 1, or more repeats of current character of p… Until we could not match any more characters.
You would need to consider the base case carefully too. That would be left as an exercise to the reader. :)

Below is the extremely concise code (Excluding comments and asserts, it’s about 10 lines of code).


1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
bool isMatch(const char *s, const char *p) {
  assert(s && p);
  if (*p == '\0') return *s == '\0';
 
  // next char is not '*': must match current character
  if (*(p+1) != '*') {
    assert(*p != '*');
    return ((*p == *s) || (*p == '.' && *s != '\0')) && isMatch(s+1, p+1);
  }
  // next char is '*'
  while ((*p == *s) || (*p == '.' && *s != '\0')) {
    if (isMatch(s, p+2)) return true;
    s++;
  }
  return isMatch(s, p+2);
}

Further Thoughts:
Some extra exercises to this problem:

If you think carefully, you can exploit some cases that the above code runs in exponential complexity. Could you think of some examples? How would you make the above code more efficient?
Try to implement partial matching instead of full matching. In addition, add ‘^’ and ‘$’ to the rule. ‘^’ matches the starting position within the string, while ‘$’ matches the ending position of the string.
Try to implement wildcard matching where ‘*’ means any sequence of zero or more characters.
For the interested reader, real world regular expression matching (such as the grep tool) are usually implemented by applying formal language theory. To understand more about it, you may read this article.

http://swtch.com/~rsc/regexp/regexp1.html


In case s=”a…..ab” p=”a*a*….a*”, it takes exponential time

http://www.regular-expressions.info/dot.html

why we need:

assert(*p != ‘*’), which is after if (*(p+1) != ‘*’)

This is to assume that multiple *’s are not in the input pattern and before a * there must be a letter to match, or else the code above will not be correct. In the case where multiple *’s can be in the input pattern, you can just use a loop to skip those, as those are redundant and won’t affect the correctness.
 */

#include <iostream>

bool isMatch( const char * s, const char * p ) {
    
    while ( *p && *s ) {
        
        //if next character from the pattern string is not null
        if ( *( p + 1 ) ) {
            if ( *( p + 1 ) == '*' ) {
                if ( *p == '.' ) {//.*
                    
                    while ( *s )
                        if ( isMatch( s, p + 2 ) )
                            return true;
                        else
                            ++s;

                    return isMatch( s, p + 2 );

                } else {
                    if ( *p != *s )
                        return isMatch( s, p + 2 );
                    else {
                        char c = *s;
                        while ( *s == c )
                            if ( isMatch( s, p + 2 ) )
                                return true;
                            else
                                ++s;
                        
                        return isMatch( s, p + 2 );
                    }
                }
            } else {
                if ( *p == '.' || *p == *s ) {
                    ++p;
                    ++s;
                } else {
                    return false;
                }
            }
        } else {
            if ( *p == '.' || *p == *s ) {
                ++p;
                ++s;
            } else {
                return false;
            }
        }
    }
    
    if ( ! *p ) {
        return ! *s;
    } else {//s points to nul character but p points to non-nul character
        //handle case like "" against "c*c*"
        while ( *p && *( p + 1 ) == '*' )
            p += 2;

        return ! *p;
    }
}

int main() {

    std::cout << isMatch( "aa", "a" ) << std::endl;
    std::cout << isMatch( "aa", "aa" ) << std::endl;
    std::cout << isMatch( "aaa", "aa" ) << std::endl;
    std::cout << isMatch( "aa", "a*" ) << std::endl;
    std::cout << isMatch( "aa", ".*" ) << std::endl;
    std::cout << isMatch( "ab", ".*" ) << std::endl;
    std::cout << isMatch( "aab", "c*a*b" ) << std::endl;

    std::cout << isMatch( "aaa", "a.a" ) << std::endl;
    std::cout << isMatch( "aaa", "ab*a" ) << std::endl;
    std::cout << isMatch( "", "c*c*" ) << std::endl;

    return 0;
}

