#include <bits/stdc++.h>

using namespace std;

int compute( const set< int > &hs ) { return reduce( hs.begin(), hs.end() ); }

int main() {
    unordered_set< string > rules;
    string                  line;
    set< int >              hs;

    getline( cin, line );
    string s( line.begin() + line.rfind( " " ) + 1, line.end() );
    for ( size_t i( 0 ); i < s.size(); i++ ) {
        if ( s[i] == '#' ) { hs.insert( i ); }
    }
    cin.ignore( 1 );
    while ( getline( cin, line ) ) {
        if ( line.back() == '#' ) {
            rules.insert( string( line.begin(), line.begin() + 5 ) );
        }
    }

    constexpr size_t N( 50000000000 );
    size_t           prev_i( 0 );
    int              step( 0 );
    for ( size_t i( 0 ); i < N; i++ ) {
        set< int > nhs;
        for ( int i( *hs.begin() - 2 ); i <= *hs.rbegin() + 2; i++ ) {
            string key;
            for ( int j( i - 2 ); j <= i + 2; j++ ) {
                key += hs.count( j ) ? '#' : '.';
            }
            if ( rules.count( key ) ) { nhs.insert( i ); }
        }
        int current_step( compute( nhs ) - compute( hs ) );
        if ( current_step != step ) {
            step   = current_step;
            prev_i = i;
        }
        if ( i - prev_i == 100 ) {
            cout << compute( hs ) + step * ( N - i ) << endl;
            break;
        }
        hs = nhs;
    }
}
