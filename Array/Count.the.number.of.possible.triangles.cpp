/**
 * Count the number of possible triangles
 * http://www.geeksforgeeks.org/find-number-of-triangles-possible/
 */

#include <iostream>
#include <vector>
#include <algorithm>

int count_possible_triangles( std::vector< int > & nums ) {

    int c = 0;

    std::sort( nums.begin(), nums.end() );

    for ( unsigned int i = 0; i < nums.size() - 2; ++i ) {
        unsigned int k = i + 2;
        for ( unsigned int j = i + 1; j < nums.size() - 1; ++j ) {
            
            while ( k < nums.size()
                 && nums[ i ] + nums[ j ] > nums[ k ] )
                ++k;

            c += ( k - 1 - j );
        }
    }

    return c;
}

int main() {

    {
        std::vector< int > nums{ 4, 6, 3, 7 };
        std::cout << count_possible_triangles( nums ) << std::endl;
    }
    
    {
        std::vector< int > nums{ 10, 21, 22, 100, 101, 200, 300 };
        std::cout << count_possible_triangles( nums ) << std::endl;
    }

    return 0;
}
