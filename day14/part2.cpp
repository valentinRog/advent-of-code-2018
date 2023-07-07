#include <bits/stdc++.h>

using namespace std;

int main() {
    string s;
    getline( cin, s );
    vector< int > target;
    for ( const auto x : s ) { target.push_back( x - '0' ); }
    vector< int > v( { 3, 7 } );
    size_t        i1( 0 ), i2( 1 );
    deque< int >  lookup( v.begin(), v.end() );
    const auto    res = [&]() {
        while ( true ) {
            int n( v[i1] + v[i2] );
            if ( n >= 10 ) {
                v.push_back( n / 10 );
                lookup.push_back( n / 10 );
            }
            v.push_back( n % 10 );
            lookup.push_back( n % 10 );
            i1 = ( i1 + v[i1] + 1 ) % v.size();
            i2 = ( i2 + v[i2] + 1 ) % v.size();
            for ( size_t i( v.size() - lookup.size() );
                  lookup.size() >= target.size();
                  i++ ) {
                if ( equal( target.begin(), target.end(), lookup.begin() ) ) {
                    return i;
                }
                lookup.pop_front();
            }
        }
    }();
    cout << res << endl;
}
