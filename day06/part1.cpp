#include <algorithm>
#include <bits/stdc++.h>
#include <random>

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

int surface( set< Point > hs, Point p0 ) {
    hs.erase( p0 );
    deque< Point > q( { p0 } );
    set< Point >   pts;
    while ( q.size() ) {
        const Point p = move( q.front() );
        q.pop_front();
        if ( pts.count( p ) ) { continue; }
        const auto f = [&]( const Point &pp ) {
            return manhattan( p, p0 ) < manhattan( p, pp );
        };
        if ( !all_of( hs.begin(), hs.end(), f ) ) { continue; }
        pts.insert( p );
        const array< Point, 4 > nps( { p + Point{ 1, 0 },
                                       p + Point{ -1, 0 },
                                       p + Point{ 0, 1 },
                                       p + Point{ 0, -1 } } );
        for ( const auto &np : nps ) {
            const auto f = [&]( const Point &pp ) {
                return manhattan( np, pp ) > manhattan( p, pp );
            };
            if ( all_of( hs.begin(), hs.end(), f ) ) { return -1; }
            q.push_back( np );
        }
    }
    return pts.size();
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
    int res( 0 );
    for ( const auto &p : hs ) { res = max( res, surface( hs, p ) ); }
    cout << res << endl;
}
