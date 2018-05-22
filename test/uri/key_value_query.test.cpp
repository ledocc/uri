#define BOOST_TEST_MODULE uri_parser

#include <boost/test/unit_test.hpp>

#include <uri/key_value_query.hpp>



namespace uri {
namespace test {

  using StringStringMap = std::map< std::string, std::string>;

BOOST_AUTO_TEST_CASE( simple_query_to_string )
{
  StringStringMap query = { { "key1", "value1" },
                                               { "key2", "value2" },
                                               { "key3", "value3" } };

  BOOST_TEST( query_to_string(query) == "key1=value1&key2=value2&key3=value3" );
}

BOOST_AUTO_TEST_CASE( reserved_word_query_to_string )
{
  StringStringMap query = { { "key1=", "val ue1" },
                                               { "key2&", "val/ue2" },
                                               { "key3?", "val:ue3" } };

  BOOST_TEST( query_to_string(query) == "key1%3D=val%20ue1&key2%26=val%2Fue2&key3%3F=val%3Aue3" );
}

BOOST_AUTO_TEST_CASE( empty_key_or_value_query_to_string )
{
  StringStringMap query = { { "", "val ue1" },
                                               { "key2&", "" },
                                               { "key3?", "val:ue3" } };

  BOOST_TEST( query_to_string(query) == "=val%20ue1&key2%26=&key3%3F=val%3Aue3" );
}

BOOST_AUTO_TEST_CASE( empty__query_to_string )
{
  StringStringMap query;

  BOOST_TEST( query_to_string(query) == "" );
}



BOOST_AUTO_TEST_CASE( simple_string_to_query )
{
  StringStringMap query = { { "key1", "value1" },
                                               { "key2", "value2" },
                                               { "key3", "value3" } };

  BOOST_TEST( string_to_query< StringStringMap >( "key1=value1&key2=value2&key3=value3" ) == query );
}

BOOST_AUTO_TEST_CASE( reserved_string_to_word_query )
{
  StringStringMap query = { { "key1=", "val ue1" },
                                               { "key2&", "val/ue2" },
                                               { "key3?", "val:ue3" } };

  BOOST_TEST( string_to_query< StringStringMap >( "key1%3D=val%20ue1&key2%26=val%2Fue2&key3%3F=val%3Aue3" ) == query );
}

BOOST_AUTO_TEST_CASE( empty_key_or_value_string_to_query )
{
  StringStringMap query = { { "", "val ue1" },
                                               { "key2&", "" },
                                               { "key3?", "val:ue3" } };

  BOOST_TEST( string_to_query< StringStringMap >( "=val%20ue1&key2%26=&key3%3F=val%3Aue3" ) == query );
}

BOOST_AUTO_TEST_CASE( empty__string_to_query )
{
  StringStringMap query;

  BOOST_TEST( string_to_query< StringStringMap >( "" ) == query );
}



} // namespace test
} // namespace uri
