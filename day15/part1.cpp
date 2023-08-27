#include <bits/stdc++.h>
#include <optional>

using namespace std;

struct Vec2 {
    int x;
    int y;
};

bool operator<( const Vec2 &lhs, const Vec2 &rhs ) {
    return lhs.x == rhs.x ? lhs.y < rhs.y : lhs.x < rhs.x;
}

bool operator==( const Vec2 &lhs, const Vec2 &rhs ) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

Vec2 operator+( const Vec2 &lhs, const Vec2 &rhs ) {
    return { lhs.x + rhs.x, lhs.y + rhs.y };
}

ostream &operator<<( ostream &os, const Vec2 &v ) {
    return os << v.x << " " << v.y;
}

map< Vec2, int > mg;
map< Vec2, int > me;
set< Vec2 >      mw;

const array< Vec2, 4 >
    dirs( { Vec2{ 0, -1 }, Vec2{ -1, 0 }, Vec2{ 1, 0 }, Vec2{ 0, 1 } } );

void print() {
    for ( int y( 0 ); y <= mw.rbegin()->y; y++ ) {
        for ( int x( 0 ); x <= mw.rbegin()->x; x++ ) {
            if ( mg.count( Vec2{ x, y } ) ) {
                cout << "G";
            } else if ( me.count( Vec2{ x, y } ) ) {
                cout << "E";
            } else if ( mw.count( Vec2{ x, y } ) ) {
                cout << "#";
            } else {
                cout << ".";
            }
        }
        cout << "\n";
    }
}

bool is_open( Vec2 p ) {
    return !( mg.count( p ) || me.count( p ) || mw.count( p ) );
}

bool can_attack( Vec2 p, const map< Vec2, int > &target ) {
    for ( const auto d : dirs ) {
        if ( target.count( p + d ) ) { return true; }
    }
    return false;
}

Vec2 next_pos( Vec2 p, const map< Vec2, int > &target ) {
    if ( can_attack( p, target ) ) { return p; }
    struct Data {
        Vec2           p;
        vector< Vec2 > visited;
    };
    deque< Data > q( { { Data{ p, vector< Vec2 >( { p } ) } } } );
    set< Vec2 >   visited;
    while ( q.size() ) {
        const auto data = q.front();
        q.pop_front();
        if ( can_attack( data.p, target ) ) { return data.visited[1]; }
        for ( const auto d : dirs ) {
            if ( !is_open( data.p + d ) || visited.count( data.p + d ) ) {
                continue;
            }
            visited.insert( data.p + d );
            Data ndata( { data.p + d, data.visited } );
            ndata.visited.push_back( data.p + d );
            q.push_back( ndata );
        }
    }
    return p;
}

int main() {
    int y( 0 );
    for ( string line; getline( cin, line ); y++ ) {
        int x( 0 );
        for ( const auto c : line ) {
            switch ( c ) {
            case 'G': mg[Vec2{ x, y }] = 200; break;
            case 'E': me[Vec2{ x, y }] = 200; break;
            case '#': mw.insert( Vec2{ x, y } ); break;
            }
            x++;
        }
    }
    print();

    const auto k = [&]() {
        for ( int i( 0 );; i++ ) {
            set< Vec2 > done;
            for ( int y( 0 ); y <= mw.rbegin()->y; y++ ) {
                for ( int x( 0 ); x <= mw.rbegin()->x; x++ ) {
                    if ( done.count( Vec2{ x, y } ) ) { continue; }
                    const auto p( Vec2{ x, y } );
                    if ( !( mg.count( p ) || me.count( p ) ) ) { continue; }
                    auto      &m( mg.count( p ) ? mg : me );
                    auto      &target( &m == &mg ? me : mg );
                    const auto np = next_pos( p, target );
                    const auto hp( m[p] );
                    m.erase( p );
                    m[np] = hp;
                    done.insert( np );
                    if ( can_attack( np, target ) ) {
                        map< Vec2, int >::iterator t;
                        int                        hp( 201 );
                        for ( const auto d : dirs ) {
                            if ( !target.count( np + d ) ) { continue; }
                            if ( target[np + d] < hp ) {
                                t  = target.find( np + d );
                                hp = t->second;
                            }
                        }
                        t->second -= 3;
                        if ( t->second <= 0 ) { target.erase( t ); }
                        if ( !target.size() ) { return i; }
                    }
                }
            }
            print();
        }
    }();

    int         n( 0 );
    const auto &m( mg.size() ? mg : me );
    for ( const auto [_, v] : m ) { n += v; }
    cout << k << " " << n << endl;
    cout << k * n << endl;
}