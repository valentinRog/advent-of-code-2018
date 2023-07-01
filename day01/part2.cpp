#include <bits/stdc++.h>

using namespace std;

int main() {
    vector< int > v;
    for ( int n; cin >> n; v.push_back( n ) )
        ;
    int res = [&] {
        int                  freq( 0 );
        unordered_set< int > hs;
        while ( true ) {
            for ( const auto n : v ) {
                freq += n;
                if ( hs.count( freq ) ) { return freq; }
                hs.insert( freq );
            }
        }
    }();
    cout << res << endl;
}