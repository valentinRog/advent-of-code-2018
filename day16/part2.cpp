#include <bits/stdc++.h>

using namespace std;

const int               a( 1 ), b( 2 ), c( 3 );
typedef array< int, 4 > A;

bool compute( const array< set< string >, 16 > &cand,
              set< string >                    &rem,
              array< string, 16 >              &res,
              int                               i = 0 ) {
    for ( int ii( 0 ); ii < i; ii++ ) {
        if ( !cand[ii].count( res[ii] ) ) { return false; }
    }
    if ( !rem.size() ) { return true; }
    for ( const auto &s : cand[i] ) {
        if ( !rem.count( s ) ) { continue; }
        rem.erase( s );
        res[i] = s;
        if ( compute( cand, rem, res, i + 1 ) ) { return true; }
        rem.insert( s );
    }
    return false;
}

set< string > intersection( const set< string > &s1, const set< string > &s2 ) {
    set< string > s;
    set_intersection( s1.begin(),
                      s1.end(),
                      s2.begin(),
                      s2.end(),
                      inserter( s, s.begin() ) );
    return s;
}

int main() {
    vector< array< A, 3 > > v1;
    vector< A >             v2;

    ostringstream oss;
    oss << cin.rdbuf();
    string     raw( oss.str() );
    const auto f = []( char x ) { return !isdigit( x ) && !isspace( x ); };
    raw.erase( remove_if( raw.begin(), raw.end(), f ), raw.end() );
    {
        string s( raw );
        s.erase( s.begin() + s.find( "\n\n\n" ), s.end() );
        istringstream iss( s );
        deque< int >  q;
        for ( int n; iss >> n; q.push_back( n ) )
            ;
        while ( q.size() ) {
            v1.push_back( array< A, 3 >() );
            for ( auto &x : v1.back() ) {
                for ( auto &x : x ) {
                    x = q.front();
                    q.pop_front();
                }
            }
        }
    }
    {
        string s( raw );
        s.erase( s.begin(), s.begin() + s.find( "\n\n\n" ) );
        istringstream iss( s );
        deque< int >  q;
        for ( int n; iss >> n; q.push_back( n ) )
            ;
        while ( q.size() ) {
            v2.push_back( A() );
            for ( auto &x : v2.back() ) {
                x = q.front();
                q.pop_front();
            }
        }
    }

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
    fill( cand.begin(), cand.end(), names );
    for ( const auto &v : v1 ) {
        const auto   &before( v[0] );
        const auto   &ins( v[1] );
        const auto   &after( v[2] );
        set< string > s;
        for ( const auto &[k, f] : ops ) {
            if ( f( before, ins ) == after ) { s.insert( k ); }
        }
        cand[ins[0]] = intersection( cand[ins[0]], s );
    }

    array< string, 16 > res;
    compute( cand, names, res );

    A reg{ 0, 0, 0, 0 };
    for ( const auto &x : v2 ) { reg = ops[res[x[0]]]( reg, x ); }
    cout << reg[0] << endl;
}
