#include <bits/stdc++.h>
#include <limits>

using namespace std;

struct Vec2 {
    int x;
    int y;
};

bool operator<( const Vec2 &lhs, const Vec2 &rhs ) {
    return lhs.x == rhs.x ? lhs.y < rhs.y : lhs.x < rhs.x;
}

Vec2 operator+( const Vec2 &lhs, const Vec2 &rhs ) {
    return { lhs.x + rhs.x, lhs.y + rhs.y };
}

struct Point {
    Vec2 p;
    Vec2 v;
};

Vec2 top_left( const set< Vec2 > &hs ) {
    int x = min_element( hs.begin(),
                         hs.end(),
                         []( const Vec2 &lhs, const Vec2 &rhs ) {
                             return lhs.x < rhs.x;
                         } )
                ->x;
    int y = min_element( hs.begin(),
                         hs.end(),
                         []( const Vec2 &lhs, const Vec2 &rhs ) {
                             return lhs.y < rhs.y;
                         } )
                ->y;
    return { x, y };
}

Vec2 bot_right( const set< Vec2 > &hs ) {
    int x = max_element( hs.begin(),
                         hs.end(),
                         []( const Vec2 &lhs, const Vec2 &rhs ) {
                             return lhs.x < rhs.x;
                         } )
                ->x;
    int y = max_element( hs.begin(),
                         hs.end(),
                         []( const Vec2 &lhs, const Vec2 &rhs ) {
                             return lhs.y < rhs.y;
                         } )
                ->y;
    return { x, y };
}

struct Draw {
    set< Vec2 > hs;
    Vec2        tl = { 0, 0 };
    Vec2        br = { std::numeric_limits< int >::max(), 0 };

    int  diag() const { return br.x + br.y - tl.x - tl.y; }
    void draw() const {
        for ( int y( tl.y ); y <= br.y; y++ ) {
            for ( int x( tl.x ); x <= br.x; x++ ) {
                cout << ( hs.count( Vec2{ x, y } ) ? "*" : " " );
            }
            cout << "\n";
        }
    }
};

int main() {
    vector< Point > v;
    for ( string s; getline( cin, s ); ) {
        Point p;
        s.erase( s.begin(), s.begin() + s.find( "<" ) + 1 );
        s.erase( s.begin() + s.find( ">" ), s.begin() + s.find( "<" ) + 1 );
        s.erase( s.rfind( ">" ) );
        s.erase( remove( s.begin(), s.end(), ',' ), s.end() );
        istringstream iss( s );
        iss >> p.p.x >> p.p.y >> p.v.x >> p.v.y;
        v.push_back( p );
    }
    Draw draw;
    while ( true ) {
        Draw ndraw;
        for ( const auto &p : v ) { ndraw.hs.insert( p.p ); }
        ndraw.tl = top_left( ndraw.hs );
        ndraw.br = bot_right( ndraw.hs );
        if ( ndraw.diag() > draw.diag() ) {
            draw.draw();
            break;
        }
        if ( ndraw.diag() < draw.diag() ) { draw = ndraw; }
        for ( auto &p : v ) { p.p = p.p + p.v; }
    }
}
