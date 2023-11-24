#include <bits/stdc++.h>

using namespace std;

struct Vec3 {
    int x;
    int y;
    int z;

    int manhattan( const Vec3 &v = { 0, 0, 0 } ) const {
        return abs( x - v.x ) + abs( y - v.y ) + abs( z - v.z );
    }
};

bool operator==( const Vec3 &lhs, const Vec3 &rhs ) {
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.y == rhs.y;
}

Vec3 operator+( const Vec3 &lhs, const Vec3 &rhs ) {
    return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z };
}

Vec3 operator*( int n, const Vec3 &rhs ) {
    return { n * rhs.x, n * rhs.y, n * rhs.z };
}

struct Bot {
    Vec3 p;
    int  r;
};

vector< Bot > v;

int intersect( const Bot &b ) {
    return count_if( v.begin(), v.end(), [&]( const Bot &bb ) {
        return bb.p.manhattan( b.p ) <= bb.r + b.r;
    } );
}

int score( const Vec3 &p ) {
    return count_if( v.begin(), v.end(), [&]( const Bot &b ) {
        return b.p.manhattan( p ) <= b.r;
    } );
}

int main() {
    string line;
    while ( getline( cin, line ) ) {
        stringstream ss;
        replace( line.begin(), line.end(), ',', ' ' );
        line.erase( remove_if( line.begin(),
                               line.end(),
                               []( char x ) {
                                   return !isdigit( x ) && x != ' ' && x != '-';
                               } ),
                    line.end() );
        ss << line;
        v.resize( v.size() + 1 );
        auto &b( v.back() );
        ss >> b.p.x >> b.p.y >> b.p.z >> b.r;
    }

    vector< Bot > vv;
    for ( const auto &b : v ) {
        if ( intersect( b ) > 900 ) { vv.push_back( b ); }
    }

    vector< Vec3 > dirs;
    for ( int x = -1; x <= 1; x++ ) {
        for ( int y = -1; y <= 1; y++ ) {
            for ( int z = -1; z <= 1; z++ ) {
                if ( x || y || z ) { dirs.push_back( { x, y, z } ); }
            }
        }
    }

    const auto f = [&]( const Vec3 &pi, const Vec3 &pf ) {
        return all_of( vv.begin(), vv.end(), [&]( const Bot &b ) {
            if ( pi.manhattan( b.p ) <= b.r ) {
                return pf.manhattan( b.p ) <= b.r;
            }
            return pf.manhattan( b.p ) <= pi.manhattan( b.p );
        } );
    };

    auto p( vv.front().p );
    int  step( 1 << 8 );
    bool any = true;
    while ( score( p ) != static_cast< int >( vv.size() ) ) {
        if ( !any ) { step >>= 1; }
        any = false;
        for ( const auto d : dirs ) {
            if ( !( f( p, p + step * d ) ) ) { continue; }
            any = true;
            p   = p + step * d;
        }
    }

    any = true;
    while ( true ) {
        if ( !any ) { break; }
        any = false;
        for ( const auto d : dirs ) {
            if ( ( p + d ).manhattan() > p.manhattan() ) { continue; }
            if ( score( p + d ) < score( p ) ) { continue; }
            p   = p + d;
            any = true;
        }
    }

    cout << p.manhattan() << endl;
}