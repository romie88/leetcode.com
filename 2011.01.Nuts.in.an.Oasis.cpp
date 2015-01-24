/**
 * http://leetcode.com/2011/01/nuts-in-oasis-interview-question-from.html
 * Nuts in an Oasis
 *
 * January 20, 2011 in Uncategorized
 *
 * A pile of nuts is in an oasis, across a desert from a town. The pile contains ‘N’ kg of nuts, and the town is ‘D’ kilometers away from the pile.

The goal of this problem is to write a program that will compute ‘X’, the maximum amount of nuts that can be transported to the town.

The nuts are transported by a horse drawn cart that is initially next to the pile of nuts. The cart can carry at most ‘C’ kilograms of nuts at any one time. The horse uses the nuts that it is carrying as fuel. It consumes ‘F’ kilograms of nuts per kilometer traveled regardless of how much weight it is carrying in the cart. The horse can load and unload the cart without using up any nuts.

Your program should have a function that takes as input 4 real numbers D,N,F,C and returns one real number: ‘X’
 */

#include <iostream>
#include <cmath>

double transport_max_nuts( double N, double D, double C, double F ) {

    std::cout << "N = " << N << " D = " << D << " C = " << C << " F = " << F << std::endl;

    //base case:
    //we have the capacity to carry all nuts,
    //so fetch all the nuts in one trip
    if ( N <= C ) {
        double nuts_arrive_destination = N - D * F;
        return nuts_arrive_destination > 0.0
             ? nuts_arrive_destination
             : 0.0;//out of fuel!
    }
    
    //# of trips we would travel back and forth
    int num_of_trips = 2 * ( std::ceil( N / C ) - 1 ) + 1;
    double nuts_to_consume = N - C * ( std::ceil( N / C ) - 1 );
    //this is the distance you are able to travel before you
    //reach ONE LESS round trip fetching nuts
    //derived from eq: N - num_of_trips * F * traveled_distance = remaining_nuts
    double traveled_distance = nuts_to_consume / F / num_of_trips;

    //we are able to travel greater (or equal) than the remaining
    //distance, so fetch the nuts right to the destination
    if ( traveled_distance >= D )
        return N - D * F * num_of_trips;

    //calculate recursively as we travel ONE less round trip now
    return transport_max_nuts( N - nuts_to_consume, D - traveled_distance, C, F );
}

int main() {

    double N, D, C, F;

    std::cout << "Please enter N D C F: " << std::endl;
    std::cin >> N >> D >> C >> F;

    double X = transport_max_nuts( N, D, C, F );
    std::cout << "max nuts transported: " << X << std::endl;

    return 0;
}
