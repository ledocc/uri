#ifndef uri__parsers__rules__uri__character_hpp
#define uri__parsers__rules__uri__character_hpp



#include <string>

#include <boost/spirit/include/qi.hpp>



namespace uri {
namespace parsers {
namespace rules {
namespace uri {

template < typename Iterator >
class character
{
public:
    using rule_char   = boost::spirit::qi::rule< Iterator, char() >;
    using rule_string = boost::spirit::qi::rule< Iterator, std::string() >;


public:
    // clang-format off
    character()
    {
        namespace ascii = boost::spirit::ascii;


        // pchar         =  unreserved /  pct-encoded /  sub-delims / ":" / "@"
        _pchar = _unreserved | _pct_encoded | _sub_delims | ascii::char_( ":@" );
        _pchar.name( "uri.pchar" );

        // pct-encoded   = "%"    HEXDIG           HEXDIG
        _pct_encoded = ascii::char_( '%' ) >> ascii::xdigit >> ascii::xdigit;
        _pct_encoded.name( "uri.pct_encoded" );

        // unreserved    = ALPHA        / DIGIT /        "-" / "." / "_" /  "~"
        _unreserved = ascii::alpha | ascii::digit | ascii::char_( "-._~" );
        _unreserved.name( "uri.unreserved" );

        // reserved      =  gen-delims /  sub-delims
        _reserved = _gen_delims | _sub_delims;
        _reserved.name( "uri.reserved" );

        // gen-delims    = ":" / "/" / "?" / "#" / "[" / "]" / "@"
        _gen_delims = ascii::char_( ":/?#[]@" );
        _gen_delims.name( "uri.gen_delims" );

        // sub-delims    = "!" / "$" / "&" /  "'" / "(" / ")"
        //               / "*" / "+" / "," /  ";" / "="
        _sub_delims = ascii::char_( "!$&\'()*+,;=" );
        _sub_delims.name( "uri.sub_delims" );
    }
    // clang-format on

    void enable_debug()
    {
        BOOST_SPIRIT_DEBUG_NODE( _pchar );
        BOOST_SPIRIT_DEBUG_NODE( _pct_encoded );
        BOOST_SPIRIT_DEBUG_NODE( _unreserved );
        BOOST_SPIRIT_DEBUG_NODE( _reserved );
        BOOST_SPIRIT_DEBUG_NODE( _gen_delims );
        BOOST_SPIRIT_DEBUG_NODE( _sub_delims );
    }

    const rule_string & pchar() const { return _pchar; }
    const rule_string & percent_encoded() const { return _pct_encoded; }
    const rule_char &   unreserved() const { return _unreserved; }
    const rule_char &   reserved() const { return _reserved; }
    const rule_char &   gen_delims() const { return _gen_delims; }
    const rule_char &   sub_delims() const { return _sub_delims; }


private:
    rule_string _pchar;
    rule_string _pct_encoded;
    rule_char   _unreserved;
    rule_char   _reserved;
    rule_char   _gen_delims;
    rule_char   _sub_delims;
};

} // namespace uri
} // namespace rules
} // namespace parsers
} // namespace uri

#endif // uri__parsers__rules__uri__character_hpp
