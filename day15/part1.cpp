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

set< Vec2 > mg;
set< Vec2 > me;
set< Vec2 > mw;

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

bool can_attack( Vec2 p, const set< Vec2 > &target ) {
    for ( const auto d : dirs ) {
        if ( target.count( p + d ) ) { return true; }
    }
    return false;
}

Vec2 next_pos( Vec2 p, const set< Vec2 > &target ) {
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
            case 'G': mg.insert( Vec2{ x, y } ); break;
            case 'E': me.insert( Vec2{ x, y } ); break;
            case '#': mw.insert( Vec2{ x, y } ); break;
            }
            x++;
        }
    }
    print();

    for ( int i( 0 ); i < 3; i++ ) {
        set< Vec2 > done;
        for ( int y( 0 ); y <= mw.rbegin()->y; y++ ) {
            for ( int x( 0 ); x <= mw.rbegin()->x; x++ ) {
                if ( done.count( Vec2{ x, y } ) ) { continue; }
                if ( mg.count( Vec2{ x, y } ) ) {
                    const auto np = next_pos( Vec2{ x, y }, me );
                    mg.erase( Vec2{ x, y } );
                    mg.insert( np );
                    done.insert( np );
                } else if ( me.count( Vec2{ x, y } ) ) {
                    const auto np = next_pos( Vec2{ x, y }, mg );
                    me.erase( Vec2{ x, y } );
                    me.insert( np );
                    done.insert( np );
                }
            }
        }
        print();
    }
}