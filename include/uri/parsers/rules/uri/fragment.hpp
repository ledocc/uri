#ifndef uri__parsers__rules__uri__fragment_hpp
#define uri__parsers__rules__uri__fragment_hpp



#include <string>

#include <boost/spirit/include/qi.hpp>

#include <uri/parsers/rules/uri/character.hpp>



namespace uri {
namespace parsers {
namespace rules {
namespace uri {

template < typename Iterator >
class fragment
{
public:
    using rule_type = boost::spirit::qi::rule< Iterator, std::string() >;


public:
    // clang-format off
    fragment()
    {
        namespace ascii = boost::spirit::ascii;


        // fragment      = *(  pchar / "/" / "?" )
        _fragment        = *( _char.pchar() | ascii::char_("/?") );
        _fragment.name("uri.fragment");
    }
    // clang-format on

    void enable_debug() { BOOST_SPIRIT_DEBUG_NODE( _fragment ); }

    const rule_type & operator()() const { return _fragment; }


private:
    rule_type                         _fragment;
    rules::uri::character< Iterator > _char;
};

} // namespace uri
} // namespace rules
} // namespace parsers
} // namespace uri

#endif // uri__parsers__rules__uri__fragment_hpp
