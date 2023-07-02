#include <bits/stdc++.h>

using namespace std;

string::size_type compute( string &s ) {
    for ( string::size_type i( 0 ); i < s.size() - 1; i++ ) {
        if ( s[i] != s[i + 1] && toupper( s[i] ) == toupper( s[i + 1] ) ) {
            s.erase( i, 2 );
            i -= 2;
        }
    }
    return s.size();
}

int main() {
    string s;
    getline( cin, s );
    unordered_set< char > hs;
    for ( const auto c : s ) { hs.insert( toupper( c ) ); }
    string::size_type res( string::npos );
    for ( const auto c : hs ) {
        string ss( s );
        ss.erase( remove_if( ss.begin(),
                             ss.end(),
                             [&]( char x ) { return toupper( x ) == c; } ),
                  ss.end() );
        res = min( res, compute( ss ) );
    }
    cout << res << endl;
}
