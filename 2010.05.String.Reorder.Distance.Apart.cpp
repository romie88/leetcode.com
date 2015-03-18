/**
 * http://articles.leetcode.com/2010/05/here-is-another-google-phone-interview.html
 * String Reorder Distance Apart
 *
 * May 1, 2010 by 1337c0d3r
 * 
 * Given a string of lowercase characters, reorder them such that the same
 * characters are at least distance d from each other.
 *
 * Input: { a, b, b }, distance = 2
 * Output: { b, a, b }
 *
 * I think it’s quite an interesting question. So if you want to do some
 * brainstorming and do not wish to spoil the fun, please feel free to do so
 * and beware of the spoilers ahead.
 *
 * *** Spoilers alert! ***
 * *** Spoilers alert! ***
 * *** Spoilers alert! ***
 *
 * The solution below involves a greedy strategy, that is: The character that
 * has the most duplicates has the highest priority of being chosen to put in
 * the new list. If that character cannot be chosen (due to the distance
 * constraint), we go for the character that has the next highest priority. We
 * also use some tables to improve the efficiency. (i.e., keeping track of #
 * of duplicates of each character.)
 */

//The following is the solution code listed in the article:
#if 0
int find_max(int freq[], bool excep[]) {
    int max_i = -1;
    int max = -1;
    for (char c = 'a'; c <= 'z'; c++) {
        if (!excep[c] && freq[c] > 0 && freq[c] > max) {
            max = freq[c];
            max_i = c;
        }
    }
    return max_i;
}

void create(char* str, int d, char ans[]) {
    int n = strlen(str);
    int freq[256] = {0};
    for (int i = 0; i < n; i++)
        freq[str[i]]++;

    int used[256] = {0};
    for (int i = 0; i < n; i++) {
        bool excep[256] = {false};
        bool done = false;
        while (!done) {
            int j = find_max(freq, excep);
            if (j == -1) {
                cout << "Error!\n";
                return;
            }
            excep[j] = true;
            if (used[j] <= 0) {
                ans[i] = j;
                freq[j]--;
                used[j] = d;
                done = true;
            } 
        }
        for (int i = 0; i < 256; i++)
            used[i]--;
    }
    ans[n] = '\0';
}
#endif

//Another better solution from the replies of the article:
#if 0
#include
#include
using namespace std;

int find_max(int distance[], int freq[])
{
    int max_i = -1;
    int max = -1;

    for (char c = ‘a'; c <= 'z'; c++)
    {
        if ((distance[c] <= 0 && freq[ c ] > max ) )
        {
            max_i = c;
            max = freq[c];
        }
    }

    return max_i;
}

void create(char *str, int d, char ans[])
{
    int n = strlen(str);
    int freq[256] = {0};
    for (int i = 0; i < n; i++)
        freq[str[i]]++;

    int distance[256] = {0};
    for (int i = 0; i < n; i++)
    {
        int j = find_max(distance, freq);

        if (j == -1)
        {
            cout << "Error\n";
            return;
        }

        ans[i] = j;
        freq[j]–;
        distance[j] = d;

        for (int i = 0; i < 256; i++)
            distance[i]–;
    }

    ans[n] = '\0';
}

int main()
{
    char str[] = "aaaabbbccceedd";
    char ans[100];
    int distance = 2;
    create(str, 2, ans);

    for (int i = 0; i < strlen(str); i++)
        cout << ans[i] << ", ";
    cout << "\n";

    return 0;
}
#endif

/**
 * Some comments said that the idea of this problem is similar of the
 * Rate-monotonic scheduling algorithm in Operating System.
 */

#include <iostream>
#include <string>
#include <unordered_map>

struct FreqDist {
    int freq;
    int dist;
    FreqDist() : freq( 1 ), dist( 0 ) {}
};

char find_max( const std::unordered_map< char, FreqDist > & m ) {
    int max_c = 0;
    int max_freq = 0;
    for ( const auto & i : m ) {
        if ( i.second.freq > max_freq
          && i.second.dist <= 0 ) {
            max_c = i.first;
            max_freq = i.second.freq;
        }
    }
    return max_c;
}

bool reorder_by_distance( const std::string & s, int d, std::string & t ) {
    
    std::unordered_map< char, FreqDist > m;
    for ( const auto c : s ) {
        auto it = m.find( c );
        if ( it == m.end() )
            m.insert( std::make_pair( c, FreqDist() ) );
        else
            ++(it->second.freq);
    }

    for ( std::string::size_type i = 0; i < s.size(); ++i ) {
        int c = find_max( m );
        if ( c == 0 ) {
            std::cout << "Not able to reorder " << s << " by distance " << d << std::endl;
            return false;
        } else {
            --m[ c ].freq;
            m[ c ].dist = d;
            t.append( 1, c );
            for ( auto & i : m ) {
                if ( i.second.freq > 0 && i.second.dist > 0 )
                    --i.second.dist;
            }
        }
    }
    
    return true;
}

int main()
{
    std::string s( "aaaabbbccceedd" );
    std::string t;
    int d = 3;
    reorder_by_distance( s, d, t );
    std::cout << s << std::endl;
    std::cout << t << std::endl;
    
    return 0;
}
