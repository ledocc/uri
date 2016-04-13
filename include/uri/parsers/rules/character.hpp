#ifndef uri__parsers__rules__character_hpp
#define uri__parsers__rules__character_hpp



#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/fusion/include/std_tuple.hpp>



namespace phoenix = boost::phoenix;
namespace fusion = boost::fusion;
namespace spirit = boost::spirit;
namespace ascii = boost::spirit::ascii;
namespace qi = boost::spirit::qi;

namespace uri { namespace parsers { namespace rules {


template <typename Iterator>
struct character
{
    using rule_char   = qi::rule<Iterator, char()>;
    using rule_string = qi::rule<Iterator, std::string()>;

    character()
    {
        // pchar         =  unreserved /  pct-encoded /  sub-delims / ":" / "@"
        _pchar           = _unreserved | _pct_encoded | _sub_delims | ascii::char_(":@");

        // pct-encoded   = "%"    HEXDIG           HEXDIG
        _pct_encoded     = ascii::char_('%') >> ascii::xdigit >> ascii::xdigit;

        // unreserved    = ALPHA        / DIGIT /        "-" / "." / "_" /  "~"
        _unreserved      = ascii::alpha | ascii::digit | ascii::char_("-._~");

        // reserved      =  gen-delims /  sub-delims
        _reserved        = _gen_delims | _sub_delims;

        // gen-delims    = ":" / "/" / "?" / "#" / "[" / "]" / "@"
        _gen_delims      = ascii::char_(":/?#[]@");

        // sub-delims    = "!" / "$" / "&" /  "'" / "(" / ")"
        //               / "*" / "+" / "," /  ";" / "="
        _sub_delims      = ascii::char_("!$&\'()*+,;=");
    }


    const rule_string & pchar() const           { return _pchar; }
    const rule_string & percent_encoded() const { return _pct_encoded; }
    const rule_char &   unreserved() const      { return _unreserved; }
    const rule_char &   reserved() const        { return _reserved; }
    const rule_char &   gen_delims() const      { return _gen_delims; }
    const rule_char &   sub_delims() const      { return _sub_delims; }


private:
    rule_string _pchar;
    rule_string _pct_encoded;
    rule_char _unreserved;
    rule_char _reserved;
    rule_char _gen_delims;
    rule_char _sub_delims;
};

}}} // namespace uri::parsers::grammar

#endif // uri__parsers__grammars__grammar_hpp
