#include <bits/stdc++.h>

using namespace std;

struct Vec2 {
    int x;
    int y;
};

bool operator==( const Vec2 &lhs, const Vec2 &rhs ) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

Vec2 operator+( const Vec2 &lhs, const Vec2 &rhs ) {
    return { lhs.x + rhs.x, lhs.y + rhs.y };
}

Vec2 &operator+=( Vec2 &lhs, const Vec2 &rhs ) { return lhs = lhs + rhs; }

Vec2 operator*( int lhs, const Vec2 &rhs ) {
    return { lhs * rhs.x, lhs * rhs.y };
}

namespace std {
template <> struct hash< Vec2 > {
    size_t operator()( const Vec2 &v ) const {
        return hash< int >()( v.x ) ^ hash< int >()( v.y );
    }
};
}

Vec2 target;
int  depth;

static int ero_level( Vec2 p );

static int geo_index( Vec2 p ) {
    if ( p == target ) { return 0; }
    if ( p == Vec2{ 0, 0 } ) { return 0; }
    if ( p.y == 0 ) { return p.x * 16807; }
    if ( p.x == 0 ) { return p.y * 48271; }
    return ero_level( Vec2{ p.x - 1, p.y } )
           * ero_level( Vec2{ p.x, p.y - 1 } );
}

static int ero_level( Vec2 p ) {
    static unordered_map< Vec2, int > cache;
    if ( cache.count( p ) ) { return cache.at( p ); }
    return cache[p] = ( geo_index( p ) + depth ) % 20183;
}

int main() {
    string       line;
    stringstream ss;
    while ( getline( cin, line ) ) {
        replace( line.begin(), line.end(), ',', ' ' );
        line.erase(
            remove_if( line.begin(),
                       line.end(),
                       []( char x ) { return !isdigit( x ) && x != ' '; } ),
            line.end() );
        ss << line;
    }
    ss >> depth >> target.x >> target.y;

    int n( 0 );
    for ( int y( 0 ); y <= target.y; y++ ) {
        for ( int x( 0 ); x <= target.x; x++ ) {
            n += ero_level( { x, y } ) % 3;
        }
    }
    cout << n << endl;
}