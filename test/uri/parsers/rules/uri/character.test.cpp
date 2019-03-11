#define BOOST_TEST_MODULE uri__parsers__rules__uri__character_hpp
#include <boost/test/unit_test.hpp>



#include <uri/parsers/rules/uri/character.hpp>

#include <boost/range/irange.hpp>

#include <vector>



namespace uri {
namespace parsers {
namespace rules {
namespace uri {
namespace test {

using char_bool_map = std::map< char, bool >;
char_bool_map createCharMap()
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

template < typename Expr >
void test_char_parser( const std::string & src, Expr const & expr, bool expectedResult )
{
    auto first = src.begin();
    auto last  = src.end();

    std::string result;
    bool        parseResult = boost::spirit::qi::parse( first, last, expr, result );
    BOOST_TEST( ( parseResult && ( first == last ) && ( result == src ) ) == expectedResult );
}

//--------------------------------------------------------------------------------------------------------------------//

template < typename Expr >
void test_char_parser( char src, Expr const & expr, bool parseResult )
{
    test_char_parser( std::string{ src }, expr, parseResult );
}

//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//

BOOST_AUTO_TEST_CASE( pchar )
{
    character< std::string::const_iterator > character;

    auto map = createCharMap();
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

    for ( auto v : map ) { test_char_parser( v.first, character.pchar(), v.second ); }
    test_char_parser( "%00", character.pchar(), true );
}

//--------------------------------------------------------------------------------------------------------------------//

BOOST_AUTO_TEST_CASE( percent_encoded )
{
    character< std::string::const_iterator > character;

    test_char_parser( "%0", character.percent_encoded(), false );
    test_char_parser( "%00", character.percent_encoded(), true );
    test_char_parser( "%000", character.percent_encoded(), false );
}

//--------------------------------------------------------------------------------------------------------------------//

BOOST_AUTO_TEST_CASE( unreserved )
{
    character< std::string::const_iterator > character;

    auto map = createCharMap();
    enable( map, '0', '9' );
    enable( map, 'a', 'z' );
    enable( map, 'A', 'Z' );
    enable( map, '-' );
    enable( map, '.' );
    enable( map, '_' );
    enable( map, '~' );

    for ( auto v : map ) { test_char_parser( v.first, character.unreserved(), v.second ); }
}

//--------------------------------------------------------------------------------------------------------------------//

BOOST_AUTO_TEST_CASE( reserved )
{
    character< std::string::const_iterator > character;

    auto map = createCharMap();
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

    for ( auto v : map ) { test_char_parser( v.first, character.reserved(), v.second ); }
}

//--------------------------------------------------------------------------------------------------------------------//

BOOST_AUTO_TEST_CASE( gen_delims )
{
    character< std::string::const_iterator > character;

    auto map = createCharMap();
    enable( map, ':' );
    enable( map, '/' );
    enable( map, '?' );
    enable( map, '#' );
    enable( map, '[' );
    enable( map, ']' );
    enable( map, '@' );

    for ( auto v : map ) { test_char_parser( v.first, character.gen_delims(), v.second ); }
}

//--------------------------------------------------------------------------------------------------------------------//

BOOST_AUTO_TEST_CASE( sub_delims )
{
    character< std::string::const_iterator > character;

    auto map = createCharMap();
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

    for ( auto v : map ) { test_char_parser( v.first, character.sub_delims(), v.second ); }
}

} // namespace test
} // namespace uri
} // namespace rules
} // namespace parsers
} // namespace uri
