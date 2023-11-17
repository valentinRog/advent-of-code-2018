#include <bits/stdc++.h>

using namespace std;

struct Vec3 {
    int x;
    int y;
    int z;

    int manhattan( const Vec3 &v ) const {
        return abs( x - v.x ) + abs( y - v.y ) + abs( z - v.z );
    }
};

struct Bot {
    Vec3 p;
    int  r;
};

int main() {
    string        line;
    vector< Bot > v;
    while ( getline( cin, line ) ) {
        stringstream ss;
        replace( line.begin(), line.end(), ',', ' ' );
        line.erase( remove_if( line.begin(),
                               line.end(),
                               []( char x ) {
                                   return !isdigit( x ) && x != ' ' && x != '-';
                               } ),
                    line.end() );
        ss << line;
        v.resize( v.size() + 1 );
        auto &b( v.back() );
        ss >> b.p.x >> b.p.y >> b.p.z >> b.r;
    }
    const auto &b = *max_element(
        v.begin(),
        v.end(),
        [&]( const Bot &lhs, const Bot &rhs ) { return lhs.r < rhs.r; } );
    const auto res = count_if( v.begin(), v.end(), [&]( const Bot &x ) {
        return b.p.manhattan( x.p ) <= b.r;
    } );
    cout << res << endl;
}