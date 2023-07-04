#include <bits/stdc++.h>

using namespace std;

struct Square {
    int x;
    int y;
    int power;
    int off;
};

int main() {
    constexpr int       W( 300 );
    int                 serial;
    const auto          power( [&]( int x, int y ) {
        int id( x + 10 );
        return ( id * y + serial ) * id / 100 % 10 - 5;
    } );
    array< int, W * W > table( { 0 } );
    const auto          compute = [&]( int tx, int ty, int bx, int by ) {
        int res( table[by * W + bx] );
        if ( tx && ty ) { res += table[( ty - 1 ) * W + tx - 1]; }
        if ( tx ) { res -= table[by * W + tx - 1]; }
        if ( ty ) { res -= table[( ty - 1 ) * W + bx]; }
        return res;
    };

    cin >> serial;
    for ( int y( 0 ); y < W; y++ ) {
        int n( 0 );
        for ( int x( 0 ); x < W; x++ ) {
            n += power( x + 1, y + 1 );
            table[y * W + x] = n;
            if ( y ) { table[y * W + x] += table[( y - 1 ) * W + x]; }
        }
    }

    Square res;
    res.power = numeric_limits< int >::min();
    for ( int y( 0 ); y < W; y++ ) {
        for ( int x( 0 ); x < W; x++ ) {
            for ( int off( 0 ); x + off < W && y + off < W; off++ ) {
                Square s( { x, y, compute( x, y, x + off, y + off ), off } );
                res = max( res, s, []( const Square &lhs, const Square &rhs ) {
                    return lhs.power < rhs.power;
                } );
            }
        }
    }
    cout << res.x + 1 << "," << res.y + 1 << "," << res.off + 1 << endl;
}