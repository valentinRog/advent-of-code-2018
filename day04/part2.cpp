#include <bits/stdc++.h>

using namespace std;

struct Date {
    int m;
    int d;
    int h;
    int mi;
};

ostream &operator<<( ostream &os, const Date &d ) {
    return os << d.m << ' ' << d.d << ' ' << d.h << ' ' << d.mi;
}

bool operator<( const Date &lhs, const Date &rhs ) {
    array< int, 4 > a1( { lhs.m, lhs.d, lhs.h, lhs.mi } );
    array< int, 4 > a2( { rhs.m, rhs.d, rhs.h, rhs.mi } );
    return lexicographical_compare( a1.begin(),
                                    a1.end(),
                                    a2.begin(),
                                    a2.end() );
}

struct Sleep {
    int start;
    int end;
};

int main() {
    map< Date, string > m;
    for ( string s; getline( cin, s ); ) {
        s = s.erase( 0, s.find( "-" ) );
        string charset( "-:" );
        replace_if(
            s.begin(),
            s.end(),
            [&]( char x ) { return charset.find( x ) != string::npos; },
            ' ' );
        istringstream iss( s );
        Date          d;
        iss >> d.m >> d.d >> d.h >> d.mi;
        s.erase( 0, s.find( "]" ) + 2 );
        m[d] = s;
    }
    map< int, vector< Sleep > > guards;
    int                         g, start;
    for ( const auto &[k, v] : m ) {
        istringstream iss( v );
        string        action;
        iss >> action;
        if ( action == "Guard" ) {
            iss.ignore( 2 );
            iss >> g;
        } else if ( action == "falls" ) {
            start = k.mi;
        } else {
            guards[g].push_back( Sleep{ start, k.mi } );
        }
    }
    int id, n( 0 ), mi;
    for ( const auto &[k, v] : guards ) {
        array< int, 60 > a( { 0 } );
        for ( const auto &x : v ) {
            for ( int i( x.start ); i < x.end; i++ ) { a[i]++; }
        }
        const auto it = max_element( a.begin(), a.end() );
        if ( *it > n ) {
            id = k;
            n  = *it;
            mi = static_cast< int >( distance( a.begin(), it ) );
        }
    }
    cout << id * mi << endl;
}
