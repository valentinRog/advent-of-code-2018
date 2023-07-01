#include <bits/stdc++.h>

using namespace std;

struct Point {
    int x;
    int y;
};

struct Claim {
    int off_x;
    int off_y;
    int w;
    int h;
};

bool operator<( const Point &lhs, const Point &rhs ) {
    return lhs.x == rhs.x ? lhs.y < rhs.y : lhs.x < rhs.x;
}

int main() {
    set< Point >                hs;
    set< Point >                intersect;
    unordered_map< int, Claim > claims;
    for ( string s; getline( cin, s ); ) {
        s.erase( s.find( "#" ), 1 );
        s.erase( s.find( "@" ), 1 );
        s.erase( s.find( ":" ), 1 );
        s.replace( s.find( "," ), 1, " " );
        s.replace( s.find( "x" ), 1, " " );
        istringstream iss( s );
        int           id;
        Claim         c;
        iss >> id >> c.off_x >> c.off_y >> c.w >> c.h;
        claims[id] = c;
        for ( int x( c.off_x ); x < c.w + c.off_x; x++ ) {
            for ( int y( c.off_y ); y < c.h + c.off_y; y++ ) {
                if ( hs.count( Point{ x, y } ) ) {
                    intersect.insert( Point{ x, y } );
                } else {
                    hs.insert( Point{ x, y } );
                }
            }
        }
    }
    const auto f = [&]( const Claim &c ) {
        for ( int x( c.off_x ); x < c.w + c.off_x; x++ ) {
            for ( int y( c.off_y ); y < c.h + c.off_y; y++ ) {
                if ( intersect.count( Point{ x, y } ) ) { return false; }
            }
        }
        return true;
    };
    auto res = find_if( claims.begin(), claims.end(), [&]( const auto& p ) {
                  return f( p.second );
              } )->first;
    cout << res << endl;
}
