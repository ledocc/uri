#define BOOST_TEST_MODULE uri__parsers__rules__uri__character_hpp
#include <boost/test/unit_test.hpp>



#include "../../test_parser.hpp"
#include "../make_char_map.hpp"

#include <uri/parsers/rules/uri/character.hpp>

#include <boost/range/irange.hpp>

#include <vector>



namespace uri {
namespace parsers {
namespace rules {
namespace uri {
namespace test {


BOOST_AUTO_TEST_CASE( pchar )
{
    character< std::string::const_iterator > character;

    auto map = rules::test::make_uri_pchar_map();

    for ( auto v : map ) { parsers::test::test_char_parser( v.first, character.pchar(), v.second ); }
    parsers::test::test_string_parser( "%00", character.pchar(), true );
}

//--------------------------------------------------------------------------------------------------------------------//

BOOST_AUTO_TEST_CASE( percent_encoded )
{
    character< std::string::const_iterator > character;

    parsers::test::test_string_parser( "%0", character.percent_encoded(), false );
    parsers::test::test_string_parser( "%00", character.percent_encoded(), true );
    parsers::test::test_string_parser( "%000", character.percent_encoded(), false );
}

//--------------------------------------------------------------------------------------------------------------------//

BOOST_AUTO_TEST_CASE( unreserved )
{
    character< std::string::const_iterator > character;

    auto map = rules::test::make_uri_unreserved_map();

    for ( auto v : map ) { parsers::test::test_char_parser( v.first, character.unreserved(), v.second ); }
}

//--------------------------------------------------------------------------------------------------------------------//

BOOST_AUTO_TEST_CASE( reserved )
{
    character< std::string::const_iterator > character;

    auto map = rules::test::make_uri_reserved_map();

    for ( auto v : map ) { parsers::test::test_char_parser( v.first, character.reserved(), v.second ); }
}

//--------------------------------------------------------------------------------------------------------------------//

BOOST_AUTO_TEST_CASE( gen_delims )
{
    character< std::string::const_iterator > character;

    auto map = rules::test::make_uri_gen_delims_map();

    for ( auto v : map ) { parsers::test::test_char_parser( v.first, character.gen_delims(), v.second ); }
}

//--------------------------------------------------------------------------------------------------------------------//

BOOST_AUTO_TEST_CASE( sub_delims )
{
    character< std::string::const_iterator > character;

    auto map = rules::test::make_uri_sub_delims_map();

    for ( auto v : map ) { parsers::test::test_char_parser( v.first, character.sub_delims(), v.second ); }
}

} // namespace test
} // namespace uri
} // namespace rules
} // namespace parsers
} // namespace uri
