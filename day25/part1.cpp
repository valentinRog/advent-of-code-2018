#include <bits/stdc++.h>

using namespace std;

typedef array< int, 4 > A4;

int man( const A4 &a1, const A4 &a2 ) {
    int n( 0 );
    for ( int i( 0 ); i < 4; i++ ) { n += abs( a1[i] - a2[i] ); }
    return n;
}

int main() {
    set< A4 > q;
    for ( string line; getline( cin, line ); ) {
        stringstream ss;
        replace( line.begin(), line.end(), ',', ' ' );
        ss << line;
        A4 a;
        for ( int i( 0 ); i < 4; i++ ) { ss >> a[i]; }
        q.insert( a );
    }
    int n( 0 );
    for ( ; q.size(); n++ ) {
        vector< A4 > v;
        v.push_back( *q.begin() );
        q.erase( q.begin() );
        while ( true ) {
            auto it = find_if( q.begin(), q.end(), [&]( const A4 &p ) {
                return any_of( v.begin(), v.end(), [&]( const A4 &pp ) {
                    return man( p, pp ) <= 3;
                } );
            } );
            if ( it == q.end() ) { break; }
            v.push_back( *it );
            q.erase( it );
        }
    }
    cout << n << endl;
}