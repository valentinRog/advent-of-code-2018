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

namespace std {
template <> struct hash< Vec2 > {
    size_t operator()( const Vec2 &v ) const {
        return hash< int >()( v.x ) ^ hash< int >()( v.y );
    }
};
}

const array< Vec2, 8 > dirs( { Vec2{ 0, -1 },
                               Vec2{ 1, -1 },
                               Vec2{ 1, 0 },
                               Vec2{ 1, 1 },
                               Vec2{ 0, 1 },
                               Vec2{ -1, 1 },
                               Vec2{ -1, 0 },
                               Vec2{ -1, -1 } } );

unordered_map< Vec2, char >
next_state( const unordered_map< Vec2, char > &state ) {
    unordered_map< Vec2, char > m;
    for ( const auto [k, v] : state ) {
        switch ( v ) {
        case '.': {
            int n = count_if( dirs.begin(), dirs.end(), [&]( const auto d ) {
                return state.count( k + d ) && state.at( k + d ) == '|';
            } );
            m[k]  = n >= 3 ? '|' : '.';
            break;
        }
        case '|': {
            int n = count_if( dirs.begin(), dirs.end(), [&]( const auto d ) {
                return state.count( k + d ) && state.at( k + d ) == '#';
            } );
            m[k]  = n >= 3 ? '#' : '|';
            break;
        }
        case '#': {
            bool c = any_of( dirs.begin(), dirs.end(), [&]( const auto d ) {
                return state.count( k + d ) && state.at( k + d ) == '#';
            } );
            c &= any_of( dirs.begin(), dirs.end(), [&]( const auto d ) {
                return state.count( k + d ) && state.at( k + d ) == '|';
            } );
            m[k] = c ? '#' : '.';
        }
        }
    }
    return m;
}

int main() {
    unordered_map< Vec2, char > state;
    string                      line;
    int                         y( 0 );
    for ( string line; getline( cin, line ); y++ ) {
        int x( 0 );
        for ( const auto c : line ) {
            state[Vec2{ x, y }] = c;
            x++;
        }
    }

    for ( int i( 0 ); i < 10; i++ ) { state = next_state( state ); }

    int n1( 0 ), n2( 0 );
    for ( const auto [_, v] : state ) {
        n1 += v == '|';
        n2 += v == '#';
    }
    cout << n1 * n2 << endl;
}