#include <bits/stdc++.h>

using namespace std;

typedef array< int, 4 > A;

int main() {
    vector< array< A, 3 > > v( { array< A, 3 >() } );
    int                     k( 0 );
    int                     i( 0 ), j( 0 );
    for ( string line; getline( cin, line ); ) {
        if ( line == "" ) {
            if ( k++ ) { break; }
            continue;
        }
        if ( j == 3 ) {
            v.push_back( array< A, 3 >() );
            j = 0;
            i++;
        }
        k            = 0;
        const auto f = []( char x ) { return !isdigit( x ) && !isspace( x ); };
        line.erase( remove_if( line.begin(), line.end(), f ), line.end() );
        istringstream iss( line );
        int           n;
        for ( int k( 0 ); k < 4; k++ ) {
            iss >> n;
            v[i][j][k] = n;
        }
        j++;
    }

    const int                                            a( 1 ), b( 2 ), c( 3 );
    typedef array< int, 4 >                              A;
    map< string, function< A( const A &, const A & ) > > ops;
    ops["addr"] = []( const A &before, const A &ins ) {
        A after( before );
        after[ins[c]] = before[ins[a]] + before[ins[b]];
        return after;
    };
    ops["addi"] = []( const A &before, const A &ins ) {
        A after( before );
        after[ins[c]] = before[ins[a]] + ins[b];
        return after;
    };
    ops["mulr"] = []( const A &before, const A &ins ) {
        A after( before );
        after[ins[c]] = before[ins[a]] * before[ins[b]];
        return after;
    };
    ops["muli"] = []( const A &before, const A &ins ) {
        A after( before );
        after[ins[c]] = before[ins[a]] * ins[b];
        return after;
    };
    ops["banr"] = []( const A &before, const A &ins ) {
        A after( before );
        after[ins[c]] = before[ins[a]] & before[ins[b]];
        return after;
    };
    ops["bani"] = []( const A &before, const A &ins ) {
        A after( before );
        after[ins[c]] = before[ins[a]] & ins[b];
        return after;
    };
    ops["borr"] = []( const A &before, const A &ins ) {
        A after( before );
        after[ins[c]] = before[ins[a]] | before[ins[b]];
        return after;
    };
    ops["bori"] = []( const A &before, const A &ins ) {
        A after( before );
        after[ins[c]] = before[ins[a]] | ins[b];
        return after;
    };
    ops["setr"] = []( const A &before, const A &ins ) {
        A after( before );
        after[ins[c]] = before[ins[a]];
        return after;
    };
    ops["seti"] = []( const A &before, const A &ins ) {
        A after( before );
        after[ins[c]] = ins[a];
        return after;
    };
    ops["gtir"] = []( const A &before, const A &ins ) {
        A after( before );
        after[ins[c]] = ins[a] > before[ins[b]];
        return after;
    };
    ops["gtri"] = []( const A &before, const A &ins ) {
        A after( before );
        after[ins[c]] = before[ins[a]] > ins[b];
        return after;
    };
    ops["gtrr"] = []( const A &before, const A &ins ) {
        A after( before );
        after[ins[c]] = before[ins[a]] > before[ins[b]];
        return after;
    };
    ops["eqir"] = []( const A &before, const A &ins ) {
        A after( before );
        after[ins[c]] = ins[a] == before[ins[b]];
        return after;
    };
    ops["eqri"] = []( const A &before, const A &ins ) {
        A after( before );
        after[ins[c]] = before[ins[a]] == ins[b];
        return after;
    };
    ops["eqrr"] = []( const A &before, const A &ins ) {
        A after( before );
        after[ins[c]] = before[ins[a]] == before[ins[b]];
        return after;
    };

    int res( 0 );
    for ( const auto &v : v ) {
        const auto &before( v[0] );
        const auto &ins( v[1] );
        const auto &after( v[2] );
        int         n( 0 );
        for ( const auto &[_, f] : ops ) { n += f( before, ins ) == after; }
        res += n >= 3;
    }
    cout << res << endl;
}