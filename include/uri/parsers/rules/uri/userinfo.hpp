#ifndef uri__parsers__rules__uri__userinfo_hpp
#define uri__parsers__rules__uri__userinfo_hpp



#include <string>

#include <boost/spirit/include/qi.hpp>

#include <uri/parsers/rules/uri/character.hpp>



namespace uri {
namespace parsers {
namespace rules {
namespace uri {

template < typename Iterator >
class userinfo
{
public:
    using rule_type = boost::spirit::qi::rule< Iterator, std::string() >;


public:
    // clang-format off
    userinfo()
    {
        namespace ascii = boost::spirit::ascii;

        // userinfo      = *(  unreserved /  pct-encoded /  sub-delims / ":" )
        _userinfo        = *( _char.unreserved() | _char.percent_encoded() | _char.sub_delims() | ascii::char_(':') );
        _userinfo.name("uri.userinfo");
    }
    // clang-format on

    void enable_debug() { BOOST_SPIRIT_DEBUG_NODE( _userinfo ); }

    const rule_type & operator()() const { return _userinfo; }


private:
    rule_type                         _userinfo;
    rules::uri::character< Iterator > _char;
};

} // namespace uri
} // namespace rules
} // namespace parsers
} // namespace uri

#endif // #define uri__parsers__rules__uri__userinfo_hpp
