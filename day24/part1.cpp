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

    int effective() const { return dmg * n; }

    int damage( const Group &g ) const {
        if ( g.immune.count( attack ) ) { return 0; }
        if ( g.weak.count( attack ) ) { return effective() * 2; }
        return effective();
    }
};

vector< Group * > immune;
vector< Group * > infection;

void fight() {
    vector< pair< Group *, Group * > > targets;
    for ( auto [a1, a2] : { make_pair( &immune, &infection ),
                            make_pair( &infection, &immune ) } ) {
        set< Group * > remain( a2->begin(), a2->end() );
        sort( a1->begin(),
              a1->end(),
              [&]( const Group *lhs, const Group *rhs ) {
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
                [&]( const Group *lhs, const Group *rhs ) {
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
    for ( auto [a1, a2] : targets ) { a2->n -= a1->damage( *a2 ) / a2->hp; }
    for ( auto a : { &immune, &infection } ) {
        vector< Group * > v;
        copy_if( a->begin(),
                 a->end(),
                 std::back_inserter( v ),
                 []( const Group *g ) { return g->n > 0; } );
        a->swap( v );
    }
}

int main() {
    auto filling( &immune );
    for ( string line; getline( cin, line ); ) {
        if ( line.find( "Infection" ) == 0 ) { filling = &infection; }
        if ( !isdigit( line.front() ) ) { continue; }
        filling->push_back( new Group( Group::parse( line ) ) );
    }
    while ( immune.size() && infection.size() ) { fight(); }
    int res( 0 );
    for ( const auto x : infection ) { res += x->n; }
    cout << res << endl;
}