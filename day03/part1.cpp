#include <bits/stdc++.h>

using namespace std;

struct Point {
    int x;
    int y;
};

bool operator<( const Point &lhs, const Point &rhs ) {
    return lhs.x == rhs.x ? lhs.y < rhs.y : lhs.x < rhs.x;
}

int main() {
    set< Point > hs;
    set< Point > intersect;
    for ( string s; getline( cin, s ); ) {
        s.erase( 0, s.find( "@" ) + 1 );
        string charset( ":,x" );
        replace_if(
            s.begin(),
            s.end(),
            [&]( char x ) { return charset.find( x ) != string::npos; },
            ' ' );
        istringstream iss( s );
        int           off_x, off_y, w, h;
        iss >> off_x >> off_y >> w >> h;
        for ( int x( off_x ); x < w + off_x; x++ ) {
            for ( int y( off_y ); y < h + off_y; y++ ) {
                if ( hs.count( Point{ x, y } ) ) {
                    intersect.insert( Point{ x, y } );
                } else {
                    hs.insert( Point{ x, y } );
                }
            }
        }
    }
    cout << intersect.size() << endl;
}
