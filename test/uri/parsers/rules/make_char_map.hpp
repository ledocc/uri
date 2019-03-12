#ifndef uri__parser__rules__test__make_char_map_hpp
#define uri__parser__rules__test__make_char_map_hpp



#include <uri/parsers/rules/uri/character.hpp>

#include <boost/range/irange.hpp>

#include <map>
#include <vector>



namespace uri {
namespace parsers {
namespace rules {
namespace test {

using char_bool_map = std::map< char, bool >;
char_bool_map make_char_map()
{
    char_bool_map result;
    for ( auto c : boost::irange< char >( 0, 127 ) ) { result[c] = false; }
    return result;
}

//--------------------------------------------------------------------------------------------------------------------//

void enable( char_bool_map & map, char c )
{
    map[c] = true;
}

//--------------------------------------------------------------------------------------------------------------------//

void enable( char_bool_map & map, char begin, char end )
{
    for ( auto c : boost::irange< char >( begin, end + 1 ) ) { enable( map, c ); }
}

//--------------------------------------------------------------------------------------------------------------------//

std::string make_string_with_enabled_char( char_bool_map & map )
{
    std::string result;

    std::for_each( map.begin(), map.end(), [&result]( const auto & value ) {
        if ( value.second ) { result.push_back( value.first ); }
    } );

    return result;
}

//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//

char_bool_map make_uri_pchar_map()
{
    auto map = make_char_map();
    enable( map, '0', '9' );
    enable( map, 'a', 'z' );
    enable( map, 'A', 'Z' );
    enable( map, '-' );
    enable( map, '.' );
    enable( map, '_' );
    enable( map, '~' );

    enable( map, '!' );
    enable( map, '$' );
    enable( map, '&' );
    enable( map, '\'' );
    enable( map, '(' );
    enable( map, ')' );
    enable( map, '*' );
    enable( map, '+' );
    enable( map, ',' );
    enable( map, ';' );
    enable( map, '=' );

    enable( map, ':' );
    enable( map, '@' );

    return map;
}

//--------------------------------------------------------------------------------------------------------------------//

char_bool_map make_uri_unreserved_map()
{
    auto map = make_char_map();
    enable( map, '0', '9' );
    enable( map, 'a', 'z' );
    enable( map, 'A', 'Z' );
    enable( map, '-' );
    enable( map, '.' );
    enable( map, '_' );
    enable( map, '~' );

    return map;
}

//--------------------------------------------------------------------------------------------------------------------//

char_bool_map make_uri_reserved_map()
{
    auto map = make_char_map();
    enable( map, ':' );
    enable( map, '/' );
    enable( map, '?' );
    enable( map, '#' );
    enable( map, '[' );
    enable( map, ']' );
    enable( map, '@' );

    enable( map, '!' );
    enable( map, '$' );
    enable( map, '&' );
    enable( map, '\'' );
    enable( map, '(' );
    enable( map, ')' );
    enable( map, '*' );
    enable( map, '+' );
    enable( map, ',' );
    enable( map, ';' );
    enable( map, '=' );

    return map;
}

//--------------------------------------------------------------------------------------------------------------------//

char_bool_map make_uri_gen_delims_map()
{
    auto map = make_char_map();
    enable( map, ':' );
    enable( map, '/' );
    enable( map, '?' );
    enable( map, '#' );
    enable( map, '[' );
    enable( map, ']' );
    enable( map, '@' );

    return map;
}

//--------------------------------------------------------------------------------------------------------------------//

char_bool_map make_uri_sub_delims_map()
{
    auto map = make_char_map();
    enable( map, '!' );
    enable( map, '$' );
    enable( map, '&' );
    enable( map, '\'' );
    enable( map, '(' );
    enable( map, ')' );
    enable( map, '*' );
    enable( map, '+' );
    enable( map, ',' );
    enable( map, ';' );
    enable( map, '=' );

    return map;
}

} // namespace test
} // namespace rules
} // namespace parsers
} // namespace uri

#endif // uri__parser__rules__test__make_char_map_hpp
