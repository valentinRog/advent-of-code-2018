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

const unordered_map< char, Vec2 > vdirs{
    { 'N', { 0, -1 } },
    { 'S', { 0, 1 } },
};

const unordered_map< char, Vec2 > hdirs{
    { 'W', { -1, 0 } },
    { 'E', { 1, 0 } },
};

unordered_set< Vec2 > vdoors;
unordered_set< Vec2 > hdoors;

void compute_doors( deque< char > &q, Vec2 p = { 0, 0 } ) {
    while ( q.size() ) {
        const char c( q.front() );
        q.pop_front();
        if ( c == '|' ) { q.push_front( '(' ); }
        if ( c == ')' || c == '|' ) { break; }
        if ( vdirs.count( c ) ) {
            hdoors.insert( p + vdirs.at( c ) );
            p += 2 * vdirs.at( c );
        } else if ( hdirs.count( c ) ) {
            vdoors.insert( p + hdirs.at( c ) );
            p += 2 * hdirs.at( c );
        }
        if ( c == '(' ) { compute_doors( q, p ); }
    }
}

void compute_dists( unordered_map< Vec2, int > &dists,
                    Vec2                        p = { 0, 0 },
                    int                         d = 0 ) {
    if ( !dists.insert( { p, d } ).second ) { return; }
    for ( const auto [_, v] : vdirs ) {
        if ( hdoors.count( p + v ) ) {
            compute_dists( dists, p + 2 * v, d + 1 );
        }
    }
    for ( const auto [_, v] : hdirs ) {
        if ( vdoors.count( p + v ) ) {
            compute_dists( dists, p + 2 * v, d + 1 );
        }
    }
}

int main() {
    string s;
    getline( cin, s );
    deque< char > q( s.begin() + 1, s.end() - 1 );
    compute_doors( q );

    unordered_map< Vec2, int > dists;
    compute_dists( dists );

    int xmin, xmax, ymin, ymax;
    {
        vector< Vec2 > doors;
        doors.insert( doors.end(), vdoors.begin(), vdoors.end() );
        doors.insert( doors.end(), hdoors.begin(), hdoors.end() );
        xmin = min_element(
                   doors.begin(),
                   doors.end(),
                   []( const auto p1, const auto p2 ) { return p1.x < p2.x; } )
                   ->x;
        ymin = min_element(
                   doors.begin(),
                   doors.end(),
                   []( const auto p1, const auto p2 ) { return p1.y < p2.y; } )
                   ->y;
        xmax = max_element(
                   doors.begin(),
                   doors.end(),
                   []( const auto p1, const auto p2 ) { return p1.x < p2.x; } )
                   ->x;
        ymax = max_element(
                   doors.begin(),
                   doors.end(),
                   []( const auto p1, const auto p2 ) { return p1.y < p2.y; } )
                   ->y;
    }

    int res( 0 );
    for ( int y( ymin ); y <= ymax; y++ ) {
        for ( int x( xmin ); x <= xmax; x++ ) {
            const auto p( Vec2{ x, y } );
            if ( hdoors.count( p ) ) {
                for ( const auto [_, v] : vdirs ) {
                    res = max( res, dists.at( p + v ) );
                }
            } else if ( vdoors.count( p ) ) {
                for ( const auto [_, v] : hdirs ) {
                    res = max( res, dists.at( p + v ) );
                }
            }
        }
    }
    cout << res << endl;
}