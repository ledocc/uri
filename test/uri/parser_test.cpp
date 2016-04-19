#define BOOST_TEST_MODULE uri_parser

#include <boost/test/unit_test.hpp>

#include <uri/parsers/grammars/grammar.hpp>
#include <uri/ios.hpp>


namespace protocol {
    struct default_ {};
} // namespace protocol


using uri_type = uri::basic_uri<protocol::default_>;


class CharProvider
{
public:
    CharProvider()
    {
        _alphaLowerCase = make_range('a', 'z');
        _alphaUpperCase = make_range('A', 'Z');
        _alpha = _alphaLowerCase + _alphaUpperCase;

        _numeric = make_range('0', '9');

        _alnum = _alpha + _numeric;


    }

    const std::string & alphaLowerCase() const { return _alphaLowerCase; }
    const std::string & alphaUpperCase() const { return _alphaUpperCase; }
    const std::string & alpha() const          { return _alpha; }
    const std::string & numeric() const        { return _numeric; }
    const std::string & alnum() const          { return _alnum; }


private:
    std::string make_range(char begin, char end)
    {
        std::string result(end - begin, '\0');
        std::generate(result.begin(), result.end(), [&begin]{ return ++begin; });
        return result;
    }

    std::string _alphaLowerCase;
    std::string _alphaUpperCase;
    std::string _alpha;
    std::string _numeric;
    std::string _alnum;
};

class ParserFixture
{
public:
    typedef uri::parsers::grammars::grammar<std::string::const_iterator, uri_type> uri_grammar;


public:
    bool parse(const std::string & uriString)
    {

        std::string::const_iterator iter = uriString.begin();
        std::string::const_iterator end = uriString.end();
        bool r = boost::spirit::qi::parse(iter, end, _uriGrammer, _uri);

        if (iter != end)
        {
            std::string::const_iterator some = iter+30;
            std::string context(iter, (some>end)?end:some);
            std::cout << "-------------------------\n";
            std::cout << "Parsing failed\n";
            std::cout << "stopped at: : \"" << context << "\" ...\n";
            std::cout << "-------------------------\n";
        }

        return (r && (iter == end));
    }

    void testComponents(const std::string & scheme,
                        const std::string & userinfo,
                        const std::string & host,
                        const std::string & port,
                        const std::string & path,
                        const std::string & query,
                        const std::string & fragment)
    {
        BOOST_TEST_MESSAGE(_uri);
        BOOST_TEST(_uri.scheme()   == scheme);
        BOOST_TEST(_uri.userinfo() == userinfo);
        BOOST_TEST(_uri.host()     == host);
        BOOST_TEST(_uri.port()     == port);
        BOOST_TEST(_uri.path()     == path);
        BOOST_TEST(_uri.query()    == query);
        BOOST_TEST(_uri.fragment() == fragment);
    }



    uri_grammar _uriGrammer;
    uri_type _uri;
};


BOOST_FIXTURE_TEST_CASE(parse_complete_valid_uri, ParserFixture)
{
    BOOST_TEST( parse("http://user:pass@www.google.com:8080/root/dir?query#fragment") == true );
    testComponents("http", "user:pass", "www.google.com", "8080", "/root/dir", "query", "fragment");
}

BOOST_FIXTURE_TEST_CASE(parse_invalid_scheme, ParserFixture)
{
    BOOST_TEST( parse("http#://user:pass@www.google.com:8080/root/dir?query#fragment") == false );
    BOOST_TEST_MESSAGE(_uri);
}

BOOST_FIXTURE_TEST_CASE(parse_mailto_scheme, ParserFixture)
{
    BOOST_TEST( parse("mailto:%22not%40me%22@example.org") == true );
    BOOST_TEST_MESSAGE(_uri);
}

BOOST_FIXTURE_TEST_CASE(parse_mailto_scheme_path_query, ParserFixture)
{
    _uriGrammer.enable_debug();
    BOOST_TEST( parse("mailto:user@example.org?subject=%3D%3Futf-8%3FQ%3Fcaf%3DC3%3DA9%3F%3D") == true );
    BOOST_TEST_MESSAGE(_uri);
}
