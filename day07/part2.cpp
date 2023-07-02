#include <bits/stdc++.h>

using namespace std;

int main() {
    vector< string > v;
    for ( string s; getline( cin, s ); ) {
        s.erase( s.begin() );
        s.erase(
            remove_if( s.begin(),
                       s.end(),
                       []( char x ) { return !isalpha( x ) || islower( x ); } ),
            s.end() );
        v.push_back( s );
    }
    set< char > hs;
    for ( auto x : v ) { hs.insert( { x[0], x[1] } ); }
    set< char >      tasks( hs.begin(), hs.end() );
    map< char, int > workers;
    set< char >      done;
    int              t( 0 );
    for ( ;; t++ ) {
        map< char, int > nworkers;
        for ( const auto [k, v] : workers ) {
            if ( t - v == k + 60 - 'A' + 1 ) {
                done.insert( k );
            } else {
                nworkers[k] = v;
            }
        }
        if ( done.size() == hs.size() ) { break; }
        workers = nworkers;

        for ( const auto task : tasks ) {
            if ( workers.size() == 5 ) { break; }
            const auto f = [&]( const string &x ) {
                return task == x[1] && !done.count( x[0] );
            };
            if ( any_of( v.begin(), v.end(), f ) ) { continue; }
            workers[task] = t;
        }
        for ( const auto [k, _] : workers ) { tasks.erase( k ); }
    }
    cout << t << endl;
}
