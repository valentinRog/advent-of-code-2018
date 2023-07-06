#include <bits/stdc++.h>

using namespace std;

struct ComplexHash {
    size_t operator()( const complex< int > &c ) const {
        return hash< int >{}( c.real() ) ^ ( hash< int >{}( c.imag() ) << 1 );
    }
};

struct Cart {
    complex< int >          z;
    complex< int >          d;
    deque< complex< int > > q = { complex< int >( 0, -1 ),
                                  complex< int >( 1, 0 ),
                                  complex< int >( 0, 1 ) };
};

int main() {
    unordered_map< complex< int >, char, ComplexHash > m;
    deque< Cart >                                      q;
    {
        unordered_map< char, complex< int > > dir( {
            { '^', complex< int >( 0, -1 ) },
            { 'v', complex< int >( 0, 1 ) },
            { '>', complex< int >( 1, 0 ) },
            { '<', complex< int >( -1, 0 ) },
        } );
        int                                   j( 0 );
        for ( string s; getline( cin, s ); j++ ) {
            for ( int i( 0 ); i < static_cast< int >( s.size() ); i++ ) {
                if ( string( "/\\+" ).find( s[i] ) != string::npos ) {
                    m[complex< int >( i, j )] = s[i];
                } else if ( string( "^>v<" ).find( s[i] ) != string::npos ) {
                    q.push_back( Cart{ complex< int >( i, j ), dir[s[i]] } );
                }
            }
        }
    }

    const complex< int > z = [&]() {
        while ( true ) {
            Cart x( move( q.front() ) );
            q.pop_front();
            switch ( m[x.z] ) {
            case '+':
                x.d *= x.q.front();
                x.q.push_back( x.q.front() );
                x.q.pop_front();
                break;
            case '/':
                x.d *= x.d.real() ? complex< int >( 0, -1 )
                                  : complex< int >( 0, 1 );
                break;
            case '\\':
                x.d *= x.d.real() ? complex< int >( 0, 1 )
                                  : complex< int >( 0, -1 );
                break;
            }
            x.z += x.d;
            if ( find_if( q.begin(),
                          q.end(),
                          [&]( const Cart &xx ) { return xx.z == x.z; } )
                 != q.end() ) {
                return x.z;
            }

            q.push_back( x );
        }
    }();
    cout << z.real() << "," << z.imag() << endl;
}
