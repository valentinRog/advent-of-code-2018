#include <bits/stdc++.h>
#include <cctype>
#include <exception>

using namespace std;

string compute( string rem, const vector< string > &ins, string s = "" ) {
    for ( const auto &x : ins ) {
        if ( s.find( x[0] ) > s.find( x[1] ) ) { throw exception(); }
    }
    if ( !rem.size() ) { return s; }
    for ( const auto c : rem ) {
        string nrem( rem );
        nrem.erase( nrem.find( c ), 1 );
        try {
            return compute( nrem, ins, s + c );
        } catch ( const exception & ) {}
    }
    throw exception();
}

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
    string s( hs.begin(), hs.end() );
    sort( s.begin(), s.end() );
    cout << compute( s, v ) << endl;
}
