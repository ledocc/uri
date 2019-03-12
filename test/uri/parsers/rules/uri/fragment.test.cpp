#define BOOST_TEST_MODULE uri__parsers__rules__uri__fragment_hpp
#include <boost/test/unit_test.hpp>



#include "../../test_parser.hpp"
#include "../make_char_map.hpp"

#include <uri/parsers/rules/uri/fragment.hpp>



namespace uri {
namespace parsers {
namespace rules {
namespace uri {
namespace test {

BOOST_AUTO_TEST_CASE( test_char )
{
    fragment< std::string::const_iterator > fragment;

    auto map = rules::test::make_uri_pchar_map();
    rules::test::enable( map, '/' );
    rules::test::enable( map, '?' );

    for ( auto v : map ) { parsers::test::test_char_parser( v.first, fragment(), v.second ); }
}

//--------------------------------------------------------------------------------------------------------------------//

BOOST_AUTO_TEST_CASE( test_string )
{
    fragment< std::string::const_iterator > fragment;

    auto map = rules::test::make_uri_pchar_map();
    rules::test::enable( map, '/' );
    rules::test::enable( map, '?' );

    parsers::test::test_string_parser( rules::test::make_string_with_enabled_char( map ), fragment(), true );
}


} // namespace test
} // namespace uri
} // namespace rules
} // namespace parsers
} // namespace uri
