#include <bits/stdc++.h>

using namespace std;

typedef array< int, 4 > A;

int main() {
    vector< array< A, 3 > > v;

    ostringstream oss;
    oss << cin.rdbuf();
    string raw( oss.str() );
    raw.erase( raw.begin() + raw.find( "\n\n\n" ), raw.end() );
    const auto f = []( char x ) { return !isdigit( x ) && !isspace( x ); };
    raw.erase( remove_if( raw.begin(), raw.end(), f ), raw.end() );
    istringstream iss( raw );
    deque< int >  q;
    for ( int n; iss >> n; q.push_back( n ) )
        ;
    while ( q.size() ) {
        v.push_back( array< A, 3 >() );
        for ( auto &x : v.back() ) {
            for ( auto &x : x ) {
                x = q.front();
                q.pop_front();
            }
        }
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

    int res( count_if( v.begin(), v.end(), [&]( const auto &v ) {
        const auto &before( v[0] );
        const auto &ins( v[1] );
        const auto &after( v[2] );
        int         n( count_if( ops.begin(), ops.end(), [&]( const auto &x ) {
            return x.second( before, ins ) == after;
        } ) );
        return n >= 3;
    } ) );
    cout << res << endl;
}