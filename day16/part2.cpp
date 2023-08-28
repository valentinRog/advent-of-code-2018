#include <bits/stdc++.h>

using namespace std;

const int               a( 1 ), b( 2 ), c( 3 );
typedef array< int, 4 > A;

bool compute( const vector< array< A, 3 > >                              &v,
              const map< string, function< A( const A &, const A & ) > > &ops,
              set< string >                                               rem,
              array< string, 16 >                                        &codes,
              int i = 0 ) {
    for ( const auto &vv : v ) {
        const auto &before( vv[0] );
        const auto &ins( vv[1] );
        const auto &after( vv[2] );
        if ( ins[0] >= i ) { continue; }
        if ( ops.at( codes[ins[0]] )( before, ins ) != after ) { return false; }
    }
    if ( i == 16 ) { return true; }
    for ( const auto &s : rem ) {
        auto nrem( rem );
        nrem.erase( s );
        codes[i] = s;
        if ( compute( v, ops, nrem, codes, i + 1 ) ) { return true; }
    }
    return false;
}

int main() {
    vector< array< A, 3 > > v( { array< A, 3 >() } );
    int                     k( 0 );
    int                     i( 0 ), j( 0 );
    for ( string line; getline( cin, line ); ) {
        if ( line.empty() ) {
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

    typedef array< int, 4 >                              A;
    const int                                            a( 1 ), b( 2 ), c( 3 );
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

    set< string > rem;
    for ( const auto &[k, _] : ops ) { rem.insert( k ); }
    array< string, 16 > res;
    compute( v, ops, rem, res );

    A reg{ 0, 0, 0, 0 };
    for ( string line; getline( cin, line ); ) {
        if ( line.empty() ) { continue; }
        istringstream iss( line );
        A             ins;
        iss >> ins[0] >> ins[1] >> ins[2] >> ins[3];
        reg = ops[res[ins[0]]]( reg, ins );
    }
    cout << reg[0] << endl;
}
