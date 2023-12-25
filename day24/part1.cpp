#include <bits/stdc++.h>

using namespace std;

struct G {
    int                     n;
    int                     hp;
    unordered_set< string > immune;
    unordered_set< string > weak;
    int                     dmg;
    string                  attack;
    int                     initiative;

    static G parse( const string &s ) {
        G          g;
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

    int effective() const { return dmg * n; }

    int damage( const G &g ) const {
        if ( g.immune.count( attack ) ) { return 0; }
        if ( g.weak.count( attack ) ) { return effective() * 2; }
        return effective();
    }
};

set< G * > immune;
set< G * > infection;

void fight() {
    vector< pair< G *, G * > > targets;
    vector< G * >              v1( immune.begin(), immune.end() );
    vector< G * >              v2( infection.begin(), infection.end() );
    for ( auto [a1, a2] : { make_pair( &v1, &v2 ), make_pair( &v2, &v1 ) } ) {
        set< G * > remain( a2->begin(), a2->end() );
        sort( a1->begin(), a1->end(), [&]( const G *lhs, const G *rhs ) {
            if ( lhs->effective() == rhs->effective() ) {
                return rhs->initiative < lhs->initiative;
            }
            return rhs->effective() < lhs->effective();
        } );
        for ( const auto g : *a1 ) {
            if ( !remain.size() ) { continue; }
            auto x = *max_element(
                remain.begin(),
                remain.end(),
                [&]( const G *lhs, const G *rhs ) {
                    if ( g->damage( *lhs ) == g->damage( *rhs ) ) {
                        return lhs->effective() < rhs->effective();
                    }
                    return g->damage( *lhs ) < g->damage( *rhs );
                } );
            if ( !g->damage( *x ) ) { continue; }
            targets.push_back( { g, x } );
            remain.erase( x );
        }
    }

    sort( targets.begin(), targets.end(), []( const auto lhs, const auto rhs ) {
        return rhs.first->initiative < lhs.first->initiative;
    } );
    for ( auto [a1, a2] : targets ) {
        if ( !immune.count( a1 ) && !infection.count( a1 ) ) { continue; }
        a2->n -= a1->damage( *a2 ) / a2->hp;
        if ( a2->n > 0 ) { continue; }
        for ( auto a : { &immune, &infection } ) {
            if ( !a->count( a2 ) ) { continue; }
            a->erase( a2 );
        }
    }
}

int main() {
    auto                      filling( &immune );
    vector< unique_ptr< G > > garbage;
    for ( string line; getline( cin, line ); ) {
        if ( line.find( "Infection" ) == 0 ) { filling = &infection; }
        if ( !isdigit( line.front() ) ) { continue; }
        garbage.push_back( make_unique< G >( G::parse( line ) ) );
        filling->insert( garbage.back().get() );
    }
    while ( immune.size() && infection.size() ) { fight(); }
    int n( 0 );
    for ( auto g : infection ) { n += g->n; }
    cout << n << endl;
}