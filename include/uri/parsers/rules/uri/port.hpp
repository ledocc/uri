#ifndef uri__parsers__rules__uri__port_hpp
#define uri__parsers__rules__uri__port_hpp



#include <string>

#include <boost/spirit/include/qi.hpp>



namespace uri {
namespace parsers {
namespace rules {
namespace uri {

template < typename Iterator >
class port
{
public:
    using rule_type = boost::spirit::qi::rule< Iterator, std::string() >;


public:
    // clang-format off
    port()
    {
        namespace ascii = boost::spirit::ascii;


        // port          = *DIGIT
        _port            = *ascii::digit;
        _port.name("uri.port");
    }
    // clang-format on

    void enable_debug() { BOOST_SPIRIT_DEBUG_NODE( _port ); }

    const rule_type & operator()() const { return _port; }


private:
    rule_type _port;
};

} // namespace uri
} // namespace rules
} // namespace parsers
} // namespace uri

#endif // uri__parsers__rules__uri__port_hpp
