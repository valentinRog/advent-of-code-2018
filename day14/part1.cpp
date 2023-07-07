#include <bits/stdc++.h>

using namespace std;

int main() {
    size_t n;
    cin >> n;
    vector< int > v( { 3, 7 } );
    size_t        i1( 0 ), i2( 1 );
    while ( v.size() < n + 10 ) {
        int n( v[i1] + v[i2] );
        if ( n >= 10 ) { v.push_back( n / 10 ); }
        v.push_back( n % 10 );
        i1 = ( i1 + v[i1] + 1 ) % v.size();
        i2 = ( i2 + v[i2] + 1 ) % v.size();
    }
    for ( auto it( v.begin() + n ); it != v.begin() + n + 10; it++ ) {
        cout << *it;
    }
    cout << endl;
}
