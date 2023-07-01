#include <bits/stdc++.h>
#include <cstddef>
#include <exception>
#include <unordered_set>

using namespace std;

int main() {
    vector< string > v;
    for ( string s; getline( cin, s ); v.push_back( s ) )
        ;
    const auto res = [&] {
        for ( string::size_type i( 0 ); i < v[0].size(); i++ ) {
            unordered_set< string > hs;
            for ( const auto &s : v ) {
                auto ss( s );
                ss.erase( ss.begin() + i );
                if ( hs.count( ss ) ) { return ss; }
                hs.insert( ss );
            }
        }
        throw exception();
    }();
    cout << res << endl;
}