#define BOOST_TEST_MODULE uri__algorithm
#include <boost/test/unit_test.hpp>



#include <uri/algorithm.hpp>
#include <uri/io.hpp>
#include <uri/uri.hpp>



namespace uri {
namespace test {

struct uri_test_sample
{
    uri_test_sample( const std::string & uri_string,
                     const std::string & scheme,
                     const std::string & userinfo = "",
                     const std::string & host     = "",
                     const std::string & port     = "",
                     const std::string & path     = "",
                     const std::string & query    = "",
                     const std::string & fragment = "" )
        : _uri_string( uri_string )
        , _uri( scheme, userinfo, host, port, path, query, fragment )
    {}

    const std::string _uri_string;
    const uri         _uri;
    bool              _success = true;
};
using uri_test_sample_list = std::vector< uri_test_sample >;


static uri_test_sample_list uri_test_samples = {
    // host
    { "http://google", "http", "", "google" },
    { "http://1.1.1.1", "http", "", "1.1.1.1" }
};


BOOST_AUTO_TEST_CASE( parse_uri )
{
    for ( const auto & sample : uri_test_samples )
    { BOOST_TEST( parse< uri_tag >( sample._uri_string ) == sample._uri ); }
    // TODO remove this comment when clang-format fix its "end line bug"
}

} // namespace test
} // namespace uri
