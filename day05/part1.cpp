#include <bits/stdc++.h>

using namespace std;

int main() {
    string s;
    getline( cin, s );
    for ( string::size_type i( 0 ); i < s.size() - 1; i++ ) {
        if ( s[i] != s[i + 1] && toupper( s[i] ) == toupper( s[i + 1] ) ) {
            s.erase( i, 2 );
            i -= 2;
        }
    }
    cout << s.size() << endl;
}
