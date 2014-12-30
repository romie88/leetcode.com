/**
 * http://leetcode.com/2011/08/reverse-bits.html
 * Reverse Bits
 *
 * 2011-08-06 bit operations
 *
 * Reverse bits of an unsigned integer.
 */

/**
 * There are several methods of reversing the bits of an unsigned integer. Here, we devise an algorithm using the XOR swap trick, and then optimize it using a divide and conquer methodology.

Hint:
How do you swap the ith bit with the jth bit? Try to figure out if you could use the XOR operation to do it.

The XOR swap trick:
Reversing bits could be done by swapping the n/2 least significant bits with its most significant bits. The trick is to implement a function called swapBits(i, j), which swaps the ith bit with the jth bit. If you still remember how XOR operation works: 0 ^ 0 == 0, 1 ^ 1 == 0, 0 ^ 1 == 1, and 1 ^ 0 == 1.

We only need to perform the swap when the ith bit and the jth bit are different. To test if two bits are different, we could use the XOR operation. Then, we need to toggle both ith and jth bits. We could apply the XOR operation again. By XOR-ing the ith and jth bit with 1, both bits are toggled.


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
17
typedef unsigned int uint;
uint swapBits(uint x, uint i, uint j) {
  uint lo = ((x >> i) & 1);
  uint hi = ((x >> j) & 1);
  if (lo ^ hi) {
    x ^= ((1U << i) | (1U << j));
  }
  return x;
}
 
uint reverseXor(uint x) {
  uint n = sizeof(x) * 8;
  for (uint i = 0; i < n/2; i++) {
    x = swapBits(x, i, n-i-1);
  }
  return x;
}
The run time complexity using the XOR trick to reverse bits is O(n), where n is the total number of bits in an unsigned integer.

The divide and conquer approach:
Remember how merge sort works? Let us use an example of n == 8 (one byte) to see how this works:

      01101001
    /         \
   0110      1001
  /   \     /   \
 01   10   10   01
 /\   /\   /\   /\
0 1  1 0  1 0  0 1
The first step is to swap all odd and even bits. After that swap consecutive pairs of bits, and so on…

Therefore, only a total of log(n) operations are necessary.

The below code shows a specific case where n == 32, but it could be easily adapted to larger n‘s as well.


1
2
3
4
5
6
7
8
9
uint reverseMask(uint x) {
  assert(sizeof(x) == 4); // special case: only works for 4 bytes (32 bits).
  x = ((x & 0x55555555) << 1) | ((x & 0xAAAAAAAA) >> 1);
  x = ((x & 0x33333333) << 2) | ((x & 0xCCCCCCCC) >> 2);
  x = ((x & 0x0F0F0F0F) << 4) | ((x & 0xF0F0F0F0) >> 4);
  x = ((x & 0x00FF00FF) << 8) | ((x & 0xFF00FF00) >> 8);
  x = ((x & 0x0000FFFF) << 16) | ((x & 0xFFFF0000) >> 16);
  return x;
}
Note:
These are not the only methods for reversing bits, and not necessarily the fastest way. For more ideas/algorithms to reverse bits, please visit Bit Twiddling Hacks.

http://graphics.stanford.edu/~seander/bithacks.html#BitReverseObvious
 */

#include <iostream>

/**
 * swap the ith bit and jth bit of x
 */
unsigned int swap_bits( unsigned int x, int i, int j ) {
    
    unsigned int bit_i = x >> i & 1;
    unsigned int bit_j = x >> j & 1;
    
    //if bit_i and bit_j are different, swap them
    if ( bit_i ^ bit_j )
        x ^= ( ( 1u << i ) | ( 1u << j ) );

    return x;
}

unsigned int reverse_bits( unsigned int x ) {

    const int total_bits = 8 * sizeof( unsigned int );
    for ( int i = 0; i < total_bits / 2; ++i )
        x = swap_bits( x, i, total_bits - i - 1 );

    return x;
}

int main() {
    
    unsigned int x;
    std::cout << "please enter a non-negative integer: ";
    std::cin >> x;

    std::cout << reverse_bits( x ) << std::endl;

    return 0;
}

