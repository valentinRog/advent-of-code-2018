#include <bits/stdc++.h>

using namespace std;

void rl( deque< int > &l ) {
    const auto x( move( l.front() ) );
    l.pop_front();
    l.push_back( x );
}

void rr( deque< int > &l ) {
    const auto x( move( l.back() ) );
    l.pop_back();
    l.push_front( x );
}

int main() {
    string s;
    getline( cin, s );
    const auto f = []( char x ) { return isalpha( x ) || x == ';'; };
    s.erase( remove_if( s.begin(), s.end(), f ), s.end() );
    istringstream iss( s );
    int           np, nm;
    iss >> np >> nm;
    deque< int >     q{ 0 };
    vector< size_t > scores( np, 0 );
    for ( int i( 1 ); i <= nm * 100; i++ ) {
        if ( i % 23 ) {
            for ( int i( 0 ); i < 2; i++ ) { rl( q ); }
            q.push_front( i );
            continue;
        }
        scores[( i - 1 ) % scores.size()] += i;
        for ( int i( 0 ); i < 7; i++ ) { rr( q ); }
        scores[( i - 1 ) % scores.size()] += q.front();
        q.pop_front();
    }
    cout << *max_element( scores.begin(), scores.end() ) << endl;
}
