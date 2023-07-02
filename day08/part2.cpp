#include <bits/stdc++.h>

using namespace std;

struct Node {
    vector< int >  m;
    vector< Node > c;
};

Node make_tree( deque< int > &q ) {
    Node node;
    int  nc( q[0] ), nm( q[1] );
    q.erase( q.begin(), q.begin() + 2 );
    for ( int i( 0 ); i < nc; i++ ) { node.c.push_back( make_tree( q ) ); }
    for ( auto it( q.begin() ); it != q.begin() + nm; it++ ) {
        node.m.push_back( *it );
    }
    q.erase( q.begin(), q.begin() + nm );
    return node;
}

int compute( const Node &node ) {
    if ( !node.c.size() ) { return reduce( node.m.begin(), node.m.end() ); }
    const auto f( [&]( int acc, int i ) {
        return acc
               + ( static_cast< size_t >( i - 1 ) < node.c.size()
                       ? compute( node.c[i - 1] )
                       : 0 );
    } );
    return accumulate( node.m.begin(), node.m.end(), 0, f );
}

int main() {
    deque< int > q;
    for ( int n; cin >> n; q.push_back( n ) )
        ;
    cout << compute( make_tree( q ) ) << endl;
}
