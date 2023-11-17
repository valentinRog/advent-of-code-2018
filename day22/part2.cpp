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

enum Region { ROCKY, WET, NARROW };
enum Tool { T, G, TG, NONE };

const array< set< Tool >, 3 > forbiden = { { { NONE }, { T, TG }, { G, TG } } };

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

int bfs() {
    struct Data {
        Tool tools;
        int  t;
        int  cd;
        Vec2 p;
    };

    deque< Data >           q;
    unordered_set< string > cache;

    const auto enqueue = [&]( const Data &x ) {
        if ( x.p.x < 0 || x.p.y < 0 ) { return; }
        if ( forbiden[ero_level( x.p ) % 3].count( x.tools ) ) { return; }
        ostringstream oss;
        oss << x.p.x << " " << x.p.y << " " << x.tools << " " << x.cd;
        if ( cache.count( oss.str() ) ) { return; }
        cache.insert( oss.str() );
        q.push_back( x );
    };

    enqueue( { T, 0, 0, { 0, 0 } } );
    while ( ~0 ) {
        const auto x = q.front();
        q.pop_front();

        if ( x.p == target && ( x.tools == T || x.tools == TG ) && !x.cd ) {
            return x.t;
        }

        if ( x.cd ) {
            auto nx( x );
            nx.cd--;
            nx.t++;
            enqueue( nx );
            continue;
        }

        for ( const auto tool : { T, G, TG, NONE } ) {
            auto nx( x );
            nx.cd = 6;
            nx.t++;
            nx.tools = tool;
            enqueue( nx );
        }

        for ( const auto d : {
                  Vec2{ 1, 0 },
                  Vec2{ -1, 0 },
                  Vec2{ 0, 1 },
                  Vec2{ 0, -1 },
              } ) {
            auto nx( x );
            nx.t++;
            nx.p += d;
            enqueue( nx );
        }
    }
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
    cout << bfs() << endl;
}