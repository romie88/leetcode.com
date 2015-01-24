/**
 * http://leetcode.com/2011/03/median-of-two-sorted-arrays.html
 * Median of Two Sorted Arrays
 *
 * March 28, 2011 in Uncategorized
 *
 * There are two sorted arrays A and B of size m and n respectively.
 * Find the median of the two sorted arrays. The overall run time complexity
 * should be O(log (m+n)).
 */

#include <iostream>
#include <algorithm>
using std::max;
using std::min;

double findMedian(int A[], int B[], int l, int r, int nA, int nB) {
if (l>r) return findMedian(B, A, 0/*max(0, (nA+nB)/2-nA - 1)*/, nB - 1/*min(nB,
(nA+nB)/2)*/, nB, nA);
int i = (l+r)/2;
int j = (nA+nB)/2 - i - 1;
if (j>=0 && A[i] < B[j]) return findMedian(A, B, i+1, r, nA, nB);
else if (j<nB-1 && A[i] > B[j+1]) return findMedian(A, B, l, i-1, nA, nB);
else {
if ( (nA+nB)%2 == 1 ) return A[i];
else if (i>0) return (A[i]+max(B[j], A[i-1]))/2.0;
else return (A[i]+B[j])/2.0;
}
}

double findMedianSortedArrays(int A[], int n, int B[], int m) {
return findMedian(A, B, 0, n-1, n, m);

//if (n<m) return findMedian(A, B, 0, n-1, n, m);
//else return findMedian(B, A, 0, m-1, m, n);
}

int main() {
    int a[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int b[] = { -2, -1 };

    std::cout << findMedianSortedArrays( a, 10, b, 2 ) << std::endl;

    return 0;
}

