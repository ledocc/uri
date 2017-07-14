#ifndef uri__parsers__rules__host_hpp
#define uri__parsers__rules__host_hpp



#include <string>

#include <boost/spirit/include/qi.hpp>

#include <uri/parsers/rules/character.hpp>
#include <uri/parsers/rules/ip.hpp>



namespace uri { namespace parsers { namespace rules {

template <typename Iterator>
class host
{
public:
    using rule_type = boost::spirit::qi::rule<Iterator, std::string()>;


public:
    host()
    {
        namespace ascii = boost::spirit::ascii;


        // host          =  IP-literal /  IPv4address /  reg-name
        _host            = _IP_literal | _ip.v4()     | _reg_name;
        _host.name("host");

        // IP-literal    = "["                  (  IPv6address /  IPvFuture    )   "]"
        _IP_literal      = ascii::char_('[') >> ( _ip.v6()     | _ip.vFuture() ) >> ascii::char_(']');

        // reg-name      = *(  unreserved /   pct-encoded /   sub-delims )
        _reg_name        = *( _char.unreserved() | _char.percent_encoded() | _char.sub_delims() );
    }

    void enable_debug()
    {
        BOOST_SPIRIT_DEBUG_NODE(_host);
        BOOST_SPIRIT_DEBUG_NODE(_IP_literal);
        BOOST_SPIRIT_DEBUG_NODE(_reg_name);
    }

    const rule_type & operator() () const { return _host; }


private:
    rule_type _host;
    rule_type _IP_literal;
    rule_type _reg_name;
    rules::ip<Iterator> _ip;
    rules::character<Iterator> _char;
};

}}} // namespace uri::parsers::rules

#endif // #define uri__parsers__rules__host_hpp
