#include <bits/stdc++.h>

using namespace std;

struct Square {
    int x;
    int y;
    int power;
};

int main() {
    int        serial;
    const auto power( [&]( int x, int y ) {
        int id( x + 10 );
        return ( id * y + serial ) * id / 100 % 10 - 5;
    } );
    cin >> serial;
    Square res;
    res.power = numeric_limits< int >::min();
    for ( int x( 1 ); x <= 300 - 2; x++ ) {
        for ( int y( 1 ); y <= 300 - 2; y++ ) {
            Square s( { x, y, 0 } );
            for ( int xx( 0 ); xx < 3; xx++ ) {
                for ( int yy( 0 ); yy < 3; yy++ ) {
                    s.power += power( x + xx, y + yy );
                }
            }
            res = max( res, s, []( const Square &lhs, const Square &rhs ) {
                return lhs.power < rhs.power;
            } );
        }
    }
    cout << res.x << "," << res.y << endl;
}
