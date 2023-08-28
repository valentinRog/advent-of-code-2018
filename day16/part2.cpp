#include <bits/stdc++.h>

using namespace std;

const int               a( 1 ), b( 2 ), c( 3 );
typedef array< int, 4 > A;

bool compute( const array< set< string >, 16 > &cand,
              set< string >                     rem,
              array< string, 16 >              &res,
              int                               i = 0 ) {
    for ( int ii( 0 ); ii < i; ii++ ) {
        if ( !cand[ii].count( res[ii] ) ) { return false; }
    }
    if ( !rem.size() ) { return true; }
    for ( const auto &s : rem ) {
        auto nrem( rem );
        nrem.erase( s );
        res[i] = s;
        if ( compute( cand, nrem, res, i + 1 ) ) { return true; }
    }
    return false;
}

set< string > intersection( const set< string > &s1, const set< string > &s2 ) {
    set< string > s;
    for ( const auto &x : s1 ) {
        if ( s2.count( x ) ) { s.insert( x ); }
    }
    return s;
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

    set< string > names;
    for ( const auto &[k, _] : ops ) { names.insert( k ); }
    array< set< string >, 16 > cand;
    for ( auto &x : cand ) { x = names; }
    for ( const auto &v : v ) {
        const auto   &before( v[0] );
        const auto   &ins( v[1] );
        const auto   &after( v[2] );
        set< string > s;
        for ( const auto &[k, f] : ops ) {
            if ( f( before, ins ) != after ) { continue; }
            s.insert( k );
        }
        cand[ins[0]] = intersection( cand[ins[0]], s );
    }

    array< string, 16 > res;
    compute( cand, names, res );

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
