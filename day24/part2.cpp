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

int units( const set< G * > &a ) {
    int n( 0 );
    for ( auto g : a ) { n += g->n; }
    return n;
}

vector< G > immune;
vector< G > infection;

void fight( set< G * > &immune, set< G * > &infection ) {
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

int simulate( int boost ) {
    vector< unique_ptr< G > > garbage;
    set< G * >                s1;
    for ( const auto &x : immune ) {
        garbage.push_back( make_unique< G >( x ) );
        s1.insert( garbage.back().get() );
    }
    for ( auto x : s1 ) { x->dmg += boost; }
    set< G * > s2;
    for ( const auto &x : infection ) {
        garbage.push_back( make_unique< G >( x ) );
        s2.insert( garbage.back().get() );
    }
    while ( s1.size() && s2.size() ) {
        int n( units( s1 ) + units( s2 ) );
        fight( s1, s2 );
        if ( n == units( s1 ) + units( s2 ) ) { return 0; }
    }
    return units( s1 );
}

int main() {
    auto filling( &immune );
    for ( string line; getline( cin, line ); ) {
        if ( line.find( "Infection" ) == 0 ) { filling = &infection; }
        if ( !isdigit( line.front() ) ) { continue; }
        filling->push_back( G::parse( line ) );
    }
    int n( 0 );
    for ( int i( 0 ); !n; i++ ) { n = simulate( i ); }
    cout << n << endl;
}