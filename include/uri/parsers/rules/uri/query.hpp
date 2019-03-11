#ifndef uri__parsers__rules__uri__query_hpp
#define uri__parsers__rules__uri__query_hpp



#include <string>

#include <boost/spirit/include/qi.hpp>

#include <uri/parsers/rules/uri/character.hpp>



namespace uri {
namespace parsers {
namespace rules {
namespace uri {

template < typename Iterator >
class query
{
public:
    using rule_type = boost::spirit::qi::rule< Iterator, std::string() >;


public:
    // clang-format off
    query()
    {
        namespace ascii = boost::spirit::ascii;


        // query         = *(  pchar / "/" / "?" )
        _query           = *( _char.pchar() | ascii::char_("/?") );
        _query.name("uri.query");
    }
    // clang-format on

    void enable_debug() { BOOST_SPIRIT_DEBUG_NODE( _query ); }

    const rule_type & operator()() const { return _query; }


private:
    rule_type                         _query;
    rules::uri::character< Iterator > _char;
};

} // namespace uri
} // namespace rules
} // namespace parsers
} // namespace uri

#endif // uri__parsers__rules__uri__query_hpp
