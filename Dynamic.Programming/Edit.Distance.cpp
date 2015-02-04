/**
 * Dynamic Programming | Set 5 (Edit Distance)
 * http://www.geeksforgeeks.org/dynamic-programming-set-5-edit-distance/
 *
 */

#include <iostream>
#include <string>
#include <vector>

enum class EditAction {
    DELETE,
    INSERT,
    REPLACE,
    NO_ACTION,
};

std::ostream & operator << ( std::ostream & os, const EditAction & e ) {

    switch ( e ) {
        case EditAction::DELETE:    os << "D"; break;
        case EditAction::INSERT:    os << "I"; break;
        case EditAction::REPLACE:   os << "R"; break;
        case EditAction::NO_ACTION: os << "N"; break;
    }
    
    return os;
}

struct AlignAction {
    int n;
    EditAction ea;
    AlignAction( int nn = 0, EditAction eaa = EditAction::NO_ACTION )
        : n( nn ), ea( eaa ) {}
};

std::ostream & operator << ( std::ostream & os, const AlignAction & a ) {

    os << a.n << a.ea;

    return os;
}

int edit_distance_dp_bottom_up(
        const std::string & a,
        const std::string & b ) {
    
    if ( a.length() == 0 ) return b.length();
    if ( b.length() == 0 ) return a.length();

    //E( i, j ) the min edit distance
    //between a[ 0 ... i - 1 ] and b[ 0 ... j - 1 ]
    //i is the length of the prefix of a
    //j is the length of the prefix of b
    std::vector< std::vector< int > >
        E( a.length() + 1, std::vector< int >( b.length() + 1, 0 ) );
    std::vector< std::vector< AlignAction > >
        A( a.length() + 1, std::vector< AlignAction >( b.length() + 1 ) );
    
    //Populate Base Cases:
    //E( 0, 0 ) = 0
    //E( i, 0 ) = i
    //E( 0, j ) = j
    E[ 0 ][ 0 ]    = 0;
    A[ 0 ][ 0 ].n  = 0;
    A[ 0 ][ 0 ].ea = EditAction::NO_ACTION;
    for ( unsigned i = 1; i < E.size(); ++i ) {
        E[ i ][ 0 ]    = i;
        A[ i ][ 0 ].n  = i;
        A[ i ][ 0 ].ea = EditAction::INSERT;
    }
    for ( unsigned j = 1; j < E[ 0 ].size(); ++j ) {
        E[ 0 ][ j ]    = j;
        A[ 0 ][ j ].n  = j;
        A[ 0 ][ j ].ea = EditAction::INSERT;
    }
    
    //Calculate matrix E
    //E[ i ][ j ] = min(
    //                   E[ i - 1 ][ j - 1 ] + ( a[ i - 1 ] == b[ j - 1 ] ),
    //                   E[ i - 1 ][ j ] //delete a[ i - 1 ]
    //                   E[ i ][ j - 1 ] //insert b[ j - 1 ] after a[ i - 1 ]
    //                 )
    for ( unsigned int i = 1; i < E.size(); ++i ) {
        for( unsigned int j = 1; j < E[ 0 ].size(); ++j ) {
            int delete_cost  = E[ i - 1 ][ j ] + 1;
            int insert_cost  = E[ i ][ j - 1 ] + 1;
            int replace_cost = E[ i - 1 ][ j - 1 ]
                             + ( a[ i - 1 ] == b[ j - 1 ] ? 0 : 1 );

            A[ i ][ j ].n = 1;
            if ( delete_cost <= insert_cost
              && delete_cost <= replace_cost )
                A[ i ][ j ].ea = EditAction::DELETE;
            if ( insert_cost <= delete_cost
              && insert_cost <= replace_cost )
                A[ i ][ j ].ea = EditAction::INSERT;
            if ( replace_cost <= delete_cost
              && replace_cost <= insert_cost ) {
                A[ i ][ j ].ea = EditAction::REPLACE;
                if ( a[ i - 1 ] == b[ j - 1 ] )
                    A[ i ][ j ].n = 0;
            }

            E[ i ][ j ] = std::min( std::min( delete_cost, insert_cost ),
                                    replace_cost );
        }
    }
    
    std::cout << "E matrix: " << std::endl;
    for ( const auto r : E ) {
        for ( const auto c : r )
            std::cout << c << " ";
        
        std::cout << std::endl;
    }
    std::cout << std::endl;
    
    int i = a.length(), j = b.length();
    while ( i >= 0 && j >= 0 ) {
        
        std::cout << i << ", " << j << " " << A[ i ][ j ] << std::endl;
        switch ( A[ i ][ j ].ea ) {
            case EditAction::DELETE:  --i; break;
            case EditAction::INSERT:  --j; break;
            case EditAction::REPLACE: --i; --j; break;
            case EditAction::NO_ACTION: --i; --j; break;
        }
    }
    
    return E[ a.length() ][ b.length() ];
}

int main() {

    {
        std::string a( "SUNDAY" );
        std::string b( "SATURDAY" );
        
        int ed = edit_distance_dp_bottom_up( a, b );
        std::cout << "min edit distance = " << ed << std::endl;
    }

    {
        std::string a( "INTENTION" );
        std::string b( "EXECUTION" );
        
        int ed = edit_distance_dp_bottom_up( a, b );
        std::cout << "min edit distance = " << ed << std::endl;
    }

    return 0;
}

