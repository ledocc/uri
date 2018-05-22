#define BOOST_TEST_MODULE uri_parser
#include <boost/test/unit_test.hpp>


#include <uri/percent/codec.hpp>


BOOST_AUTO_TEST_CASE(decode_char)
{
    uri::percent::code code("%21");
    BOOST_TEST(uri::percent::decode(code) == '!');
}

BOOST_AUTO_TEST_CASE(decode_string_iterator)
{
    std::string encodedString("hello%20world%2C%20nice%20day%20%3F");
    std::string decodedString;

    uri::percent::decode(std::begin(encodedString), std::end(encodedString),
                         std::back_inserter(decodedString));

    BOOST_TEST("hello world, nice day ?" == decodedString);
}

BOOST_AUTO_TEST_CASE(decode_string)
{
    std::string encodedString("hello%20world%2C%20nice%20day%20%3F");
    std::string decodedString = uri::percent::decode(encodedString);

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

BOOST_AUTO_TEST_CASE(encode_string_iterator)
{
    std::string decodedString("hello world, nice day ?");
    std::string encodedString;

    uri::percent::encode(std::begin(decodedString), std::end(decodedString),
                         std::back_inserter(encodedString));

    BOOST_TEST("hello%20world%2C%20nice%20day%20%3F" == encodedString);
}

BOOST_AUTO_TEST_CASE(encode_string)
{
    std::string decodedString("hello world, nice day ?");
    std::string encodedString = uri::percent::encode(decodedString);

    BOOST_TEST("hello%20world%2C%20nice%20day%20%3F" == encodedString);
}
