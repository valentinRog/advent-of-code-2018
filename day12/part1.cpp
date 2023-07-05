#include <iostream>
#include <numeric>
#include <set>
#include <unordered_set>

using namespace std;

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

    for ( int i( 0 ); i < 20; i++ ) {
        set< int > nhs;
        for ( int i( *hs.begin() - 2 ); i <= *hs.rbegin() + 2; i++ ) {
            string key;
            for ( int j( i - 2 ); j <= i + 2; j++ ) {
                key += hs.count( j ) ? '#' : '.';
            }
            if ( rules.count( key ) ) { nhs.insert( i ); }
        }
        hs = nhs;
    }
    cout << reduce( hs.begin(), hs.end() ) << endl;
}
