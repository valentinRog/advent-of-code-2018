#include <bits/stdc++.h>

using namespace std;

int w, h;

string adjacent( const string &state, int p ) {
    string s;
    for ( int y( -1 ); y <= 1; y++ ) {
        for ( int x( -1 ); x <= 1; x++ ) {
            if ( !x && !y ) { continue; }
            if ( p / w == 0 && y == -1 ) { continue; }
            if ( p / w == h - 1 && y == 1 ) { continue; }
            if ( p % w == 0 && x == -1 ) { continue; }
            if ( p % w == w - 1 && x == 1 ) { continue; }
            s.push_back( state[p + y * w + x] );
        }
    }
    return s;
}

string next_state( const string &state ) {
    string res;
    for ( int y( 0 ); y < h; y++ ) {
        for ( int x( 0 ); x < h; x++ ) {
            string s( adjacent( state, y * w + x ) );
            switch ( state[y * w + x] ) {
            case '.': {
                int n = count( s.begin(), s.end(), '|' );
                res.push_back( n >= 3 ? '|' : '.' );
                break;
            }
            case '|': {
                int n = count( s.begin(), s.end(), '#' );
                res.push_back( n >= 3 ? '#' : '|' );
                break;
            }
            case '#': {
                bool c = s.find( "#" ) != string::npos;
                c &= s.find( "|" ) != string::npos;
                res.push_back( c ? '#' : '.' );
            }
            }
        }
    }
    return res;
}

int main() {
    string state;
    for ( string line; getline( cin, line ); state += line ) {
        w = line.size();
    }
    h = state.size() / w;

    map< string, int > mem;
    mem[state] = 0;
    constexpr size_t n( 1000000000 );
    for ( size_t i( 0 ); i < n; i++ ) {
        state = next_state( state );
        if ( mem.count( state ) ) {
            int d( i - mem[state] );
            i += ( n - i ) / d * d;
        }
        mem[state] = i;
    }

    const auto res = count( state.begin(), state.end(), '|' )
                     * count( state.begin(), state.end(), '#' );
    cout << res << endl;
}