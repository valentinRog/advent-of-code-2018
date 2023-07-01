#include <bits/stdc++.h>

using namespace std;

int main() {
    int a( 0 ), b( 0 );
    for ( string s; getline( cin, s ); ) {
        map< char, int > m;
        for ( const auto c : s ) { m[c]++; }
        int aa( 0 ), bb( 0 );
        for ( const auto [_, v] : m ) {
            aa |= v == 2;
            bb |= v == 3;
            if ( aa && bb ) { break; }
        }
        a += aa;
        b += bb;
    }
    cout << a * b << endl;
}