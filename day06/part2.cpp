#include <bits/stdc++.h>

using namespace std;

struct Point {
    int x;
    int y;
};

ostream &operator<<( ostream &os, const Point &p ) {
    return os << p.x << "," << p.y;
}

bool operator<( const Point &p1, const Point &p2 ) {
    return p1.x == p2.x ? p1.y < p2.y : p1.x < p2.x;
}

bool operator==( const Point &p1, const Point &p2 ) {
    return p1.x == p2.x && p1.y == p2.y;
}

bool operator!=( const Point &p1, const Point &p2 ) { return !( p1 == p2 ); }

Point operator+( const Point &p1, const Point &p2 ) {
    return { p1.x + p2.x, p1.y + p2.y };
}

int manhattan( const Point &p1, const Point &p2 ) {
    return abs( p1.x - p2.x ) + abs( p1.y - p2.y );
}

void compute( const set< Point > &hs, Point p, set< Point > &res ) {
    if ( res.count( p ) ) { return; }
    if ( accumulate( hs.begin(),
                     hs.end(),
                     0,
                     [&]( int acc, const Point &pp ) {
                         return acc + manhattan( p, pp );
                     } )
         >= 10000 ) {
        return;
    }
    res.insert( p );
    compute( hs, p + Point{ 1, 0 }, res );
    compute( hs, p + Point{ -1, 0 }, res );
    compute( hs, p + Point{ 0, 1 }, res );
    compute( hs, p + Point{ 0, -1 }, res );
}

int main() {
    set< Point > hs;
    for ( string s; getline( cin, s ); ) {
        s.erase( s.find( "," ), 1 );
        Point         p;
        istringstream iss( s );
        iss >> p.x >> p.y;
        hs.insert( p );
    }
    set< Point > res;
    for ( const auto &p : hs ) { compute( hs, p, res ); }
    cout << res.size() << endl;
}
