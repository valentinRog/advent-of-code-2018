#include <bits/stdc++.h>
#include <optional>

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

namespace std {
template <> struct hash< Vec2 > {
    size_t operator()( const Vec2 &v ) const {
        return hash< int >()( v.x ) ^ hash< int >()( v.y );
    }
};
}

const Vec2             source( { 500, 0 } );
const array< Vec2, 2 > lr( { Vec2{ -1, 0 }, Vec2{ 1, 0 } } );

unordered_set< Vec2 > hs;
unordered_set< Vec2 > hsw;
unordered_set< Vec2 > hsmw;

int xmin, ymin, xmax, ymax;

bool has_floor( Vec2 p ) {
    return hs.count( p + Vec2{ 0, 1 } ) || hsw.count( p + Vec2{ 0, 1 } );
}

void fill_resting( Vec2 p = source ) {
    if ( p.y == ymax ) { return; }
    if ( !has_floor( p ) ) { return fill_resting( p + Vec2{ 0, 1 } ); }

    static unordered_set< Vec2 > cache;
    if ( cache.count( p ) ) { return; }
    cache.insert( p );

    const auto f = [&]( Vec2 d ) {
        for ( auto pp( p ); !hs.count( pp ); pp = pp + d ) {
            if ( !has_floor( pp ) ) { return optional( pp ); }
        }
        return optional< Vec2 >();
    };
    const auto left  = f( lr[0] );
    const auto right = f( lr[1] );
    if ( left.has_value() ) { fill_resting( *left ); }
    if ( right.has_value() ) { fill_resting( *right ); }
    if ( left.has_value() || right.has_value() ) { return; }

    for ( const auto d : lr ) {
        auto pp( p );
        while ( !hs.count( pp ) ) {
            hsw.insert( pp );
            pp = pp + d;
        }
    }

    return fill_resting( p + Vec2{ 0, -1 } );
}

void fill_moving( Vec2 p = source + Vec2{ 0, 1 } ) {
    if ( hsmw.count( p ) ) { return; }
    if ( p.y >= ymin ) { hsmw.insert( p ); }
    if ( p.y == ymax ) { return; }
    if ( !has_floor( p ) ) { return fill_moving( p + Vec2{ 0, 1 } ); }
    for ( const auto d : lr ) {
        if ( !hs.count( p + d ) ) { fill_moving( p + d ); }
    }
}

int main() {
    for ( string line; getline( cin, line ); ) {
        const auto f( []( const char x ) { return !isdigit( x ); } );
        replace_if( line.begin() + 1, line.end(), f, ' ' );
        istringstream iss( line );
        char          c;
        iss >> c;
        if ( c == 'x' ) {
            int x, y0, y1;
            iss >> x >> y0 >> y1;
            for ( int y( y0 ); y <= y1; y++ ) { hs.insert( Vec2{ x, y } ); }
        } else {
            int y, x0, x1;
            iss >> y >> x0 >> x1;
            for ( int x( x0 ); x <= x1; x++ ) { hs.insert( Vec2{ x, y } ); }
        }
    }

    xmin = min_element(
               hs.begin(),
               hs.end(),
               []( const auto p1, const auto p2 ) { return p1.x < p2.x; } )
               ->x;
    ymin = min_element(
               hs.begin(),
               hs.end(),
               []( const auto p1, const auto p2 ) { return p1.y < p2.y; } )
               ->y;
    xmax = max_element(
               hs.begin(),
               hs.end(),
               []( const auto p1, const auto p2 ) { return p1.x < p2.x; } )
               ->x;
    ymax = max_element(
               hs.begin(),
               hs.end(),
               []( const auto p1, const auto p2 ) { return p1.y < p2.y; } )
               ->y;

    fill_resting();
    fill_moving();
    cout << hsw.size() + hsmw.size() << endl;
}