#include <bits/stdc++.h>

using namespace std;

int compute( deque< int > &q ) {
    int nc( q[0] ), nm( q[1] );
    q.erase( q.begin(), q.begin() + 2 );
    int n( 0 );
    for ( int i( 0 ); i < nc; i++ ) { n += compute( q ); }
    n += reduce( q.begin(), q.begin() + nm );
    q.erase( q.begin(), q.begin() + nm );
    return n;
}

int main() {
    deque< int > q;
    for ( int n; cin >> n; q.push_back( n ) )
        ;
    cout << compute( q ) << endl;
}
