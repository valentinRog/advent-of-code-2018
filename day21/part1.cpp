#include <bits/stdc++.h>

using namespace std;

typedef array< int, 3 > A3;
typedef array< int, 6 > A6;

int main() {
    string line;
    getline( cin, line );
    line.erase( remove_if( line.begin(),
                           line.end(),
                           []( char x ) { return !isdigit( x ); } ),
                line.end() );
    int           ri;
    istringstream iss( line );
    iss >> ri;
    vector< pair< string, A3 > > v;
    while ( getline( cin, line ) ) {
        istringstream iss( line );
        v.push_back( pair< string, A3 >() );
        iss >> v.back().first >> v.back().second[0] >> v.back().second[1]
            >> v.back().second[2];
    }

    map< string, function< A6( const A6 &, const A3 & ) > > ops;
    ops["addr"] = []( const A6 &before, const A3 &ins ) {
        A6 after( before );
        after[ins[2]] = before[ins[0]] + before[ins[1]];
        return after;
    };
    ops["addi"] = []( const A6 &before, const A3 &ins ) {
        A6 after( before );
        after[ins[2]] = before[ins[0]] + ins[1];
        return after;
    };
    ops["mulr"] = []( const A6 &before, const A3 &ins ) {
        A6 after( before );
        after[ins[2]] = before[ins[0]] * before[ins[1]];
        return after;
    };
    ops["muli"] = []( const A6 &before, const A3 &ins ) {
        A6 after( before );
        after[ins[2]] = before[ins[0]] * ins[1];
        return after;
    };
    ops["banr"] = []( const A6 &before, const A3 &ins ) {
        A6 after( before );
        after[ins[2]] = before[ins[0]] & before[ins[1]];
        return after;
    };
    ops["bani"] = []( const A6 &before, const A3 &ins ) {
        A6 after( before );
        after[ins[2]] = before[ins[0]] & ins[1];
        return after;
    };
    ops["borr"] = []( const A6 &before, const A3 &ins ) {
        A6 after( before );
        after[ins[2]] = before[ins[0]] | before[ins[1]];
        return after;
    };
    ops["bori"] = []( const A6 &before, const A3 &ins ) {
        A6 after( before );
        after[ins[2]] = before[ins[0]] | ins[1];
        return after;
    };
    ops["setr"] = []( const A6 &before, const A3 &ins ) {
        A6 after( before );
        after[ins[2]] = before[ins[0]];
        return after;
    };
    ops["seti"] = []( const A6 &before, const A3 &ins ) {
        A6 after( before );
        after[ins[2]] = ins[0];
        return after;
    };
    ops["gtir"] = []( const A6 &before, const A3 &ins ) {
        A6 after( before );
        after[ins[2]] = ins[0] > before[ins[1]];
        return after;
    };
    ops["gtri"] = []( const A6 &before, const A3 &ins ) {
        A6 after( before );
        after[ins[2]] = before[ins[0]] > ins[1];
        return after;
    };
    ops["gtrr"] = []( const A6 &before, const A3 &ins ) {
        A6 after( before );
        after[ins[2]] = before[ins[0]] > before[ins[1]];
        return after;
    };
    ops["eqir"] = []( const A6 &before, const A3 &ins ) {
        A6 after( before );
        after[ins[2]] = ins[0] == before[ins[1]];
        return after;
    };
    ops["eqri"] = []( const A6 &before, const A3 &ins ) {
        A6 after( before );
        after[ins[2]] = before[ins[0]] == ins[1];
        return after;
    };
    ops["eqrr"] = []( const A6 &before, const A3 &ins ) {
        A6 after( before );
        after[ins[2]] = before[ins[0]] == before[ins[1]];
        return after;
    };

    A6 reg;
    fill( reg.begin(), reg.end(), 0 );
    while ( reg[ri] != 28 ) {
        reg = ops[v[reg[ri]].first]( reg, v[reg[ri]].second );
        reg[ri]++;
    }
    cout << reg[3] << endl;
}