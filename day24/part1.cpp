#include <bits/stdc++.h>

using namespace std;

struct Group {
    int                     n;
    int                     hp;
    unordered_set< string > immune;
    unordered_set< string > weak;
    int                     dmg;
    string                  attack;
    int                     initiative;

    static Group parse( const string &s ) {
        Group      g;
        const auto f = [&]( const string &w ) {
            unordered_set< string > hs;
            auto                    i = s.find( w );
            if ( i == string::npos ) { return hs; }
            string acc;
            for ( auto it( s.begin() + i + w.size() ); *it != ';' && *it != ')';
                  it++ ) {
                if ( *it == ' ' ) { continue; }
                if ( *it == ',' ) {
                    hs.insert( acc );
                    acc.clear();
                    continue;
                }
                acc.push_back( *it );
            }
            hs.insert( acc );
            return hs;
        };
        g.immune = f( "immune to" );
        g.weak   = f( "weak to" );
        auto scpy( s );
        scpy.erase(
            remove_if( scpy.begin(),
                       scpy.end(),
                       []( char x ) { return !isdigit( x ) && x != ' '; } ),
            scpy.end() );
        istringstream iss( scpy );
        iss >> g.n >> g.hp >> g.dmg >> g.initiative;
        for ( auto it( s.begin() + s.find( " damage" ) - 1 ); *it != ' ';
              it-- ) {
            g.attack.push_back( *it );
        }
        reverse( g.attack.begin(), g.attack.end() );
        return g;
    }
};

int main() {
    for ( string line; getline( cin, line ); ) {
        if ( isdigit( line[0] ) ) { Group::parse( line ); }
    }
}