#ifndef uri__parsers__rules__uri__scheme_hpp
#define uri__parsers__rules__uri__scheme_hpp



#include <string>

#include <boost/spirit/include/qi.hpp>



namespace uri {
namespace parsers {
namespace rules {
namespace uri {

template < typename Iterator >
class scheme
{
public:
    using rule_type = boost::spirit::qi::rule< Iterator, std::string() >;


public:
    // clang-format off
    scheme()
    {
        namespace ascii = boost::spirit::ascii;


        // scheme        = ALPHA           *( ALPHA        /  DIGIT       / "+" / "-" / "." )
        _scheme          = ascii::alpha >> *( ascii::alpha | ascii::digit | ascii::char_("+-.") );
        _scheme.name("uri.scheme");
    }
    // clang-format on

    void enable_debug() { BOOST_SPIRIT_DEBUG_NODE( _scheme ); }

    const rule_type & operator()() const { return _scheme; }


private:
    rule_type _scheme;
};

} // namespace uri
} // namespace rules
} // namespace parsers
} // namespace uri

#endif // uri__parsers__rules__uri__scheme_hpp
