#define BOOST_TEST_MODULE uri__uri
#include <boost/test/unit_test.hpp>



#include <uri/algorithm.hpp>
#include <uri/uri.hpp>



namespace uri {
namespace test {

BOOST_AUTO_TEST_CASE( ctor )
{
    std::string scheme   = "http";
    std::string userinfo = "toto:titi";
    std::string host     = "my.home.here";
    std::string port     = "8080";
    std::string path     = "/../../../I/enter/in/your/home";
    std::string query    = "nothing";
    std::string fragment = "1.1";

    uri my_uri( scheme, userinfo, host, port, path, query, fragment );

    BOOST_TEST( my_uri.scheme() == scheme );
    BOOST_TEST( my_uri.userinfo() == userinfo );
    BOOST_TEST( my_uri.host() == host );
    BOOST_TEST( my_uri.port() == port );
    BOOST_TEST( my_uri.path() == path );
    BOOST_TEST( my_uri.query() == query );
    BOOST_TEST( my_uri.fragment() == fragment );
}

//--------------------------------------------------------------------------------------------------------------------//

BOOST_AUTO_TEST_CASE( parse_valid_uri )
{
    std::string scheme   = "http";
    std::string userinfo = "toto:titi";
    std::string host     = "my.home.here";
    std::string port     = "8080";
    std::string path     = "/../../../I/enter/in/your/home";
    std::string query    = "nothing";
    std::string fragment = "1.1";

    std::stringstream ss;
    ss << scheme << "://" << userinfo << "@" << host << ":" << port << path << "?" << query << "#" << fragment;

    auto my_uri = parse< uri_tag >( ss.str() );

    BOOST_TEST( my_uri.scheme() == scheme );
    BOOST_TEST( my_uri.userinfo() == userinfo );
    BOOST_TEST( my_uri.host() == host );
    BOOST_TEST( my_uri.port() == port );
    BOOST_TEST( my_uri.path() == path );
    BOOST_TEST( my_uri.query() == query );
    BOOST_TEST( my_uri.fragment() == fragment );
}

} // namespace test
} // namespace uri
