#define BOOST_TEST_MODULE uri_codec

#include <boost/test/unit_test.hpp>

#include <uri/algorithm.hpp>
#include <uri/ios.hpp>


namespace protocol {
    struct default_ {};
} // namespace protocol


using uri_type = uri::basic_uri<protocol::default_>;


BOOST_AUTO_TEST_CASE(encode_uri)
{
    uri_type uri("http",
                 "user:pass",
                 "www.google.com",
                 "8080",
                 "/root/dir",
                 "query",
                 "fragment");
    uri_type encodedUri = encode(uri);

    //BOOST_TEST( encodedUri == uri );
}

