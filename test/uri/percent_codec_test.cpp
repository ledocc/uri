#define BOOST_TEST_MODULE uri_parser
#include <boost/test/unit_test.hpp>


#include <uri/percent/codec.hpp>


BOOST_AUTO_TEST_CASE(decode_char)
{
    uri::percent::code code("%21");
    BOOST_TEST(uri::percent::decode(code) == '!');
}

BOOST_AUTO_TEST_CASE(decode_string)
{
    std::string encodedString("hello%20world%2c%20nice%20day%20%3F");
    std::string decodedString;

    uri::percent::decode(std::begin(encodedString), std::end(encodedString),
                         std::back_inserter(decodedString));

    BOOST_TEST("hello world, nice day ?" == decodedString);
}


BOOST_AUTO_TEST_CASE(encode_char)
{
    uri::percent::code code;
    uri::percent::encode('!', code);
    BOOST_TEST(code[0] == '%');
    BOOST_TEST(code[1] == '2');
    BOOST_TEST(code[2] == '1');
}

