#ifndef uri__parsers__rules__host_hpp
#define uri__parsers__rules__host_hpp



#include <string>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/fusion/include/std_tuple.hpp>

#include <uri/parsers/rules/character.hpp>
#include <uri/parsers/rules/ip.hpp>



namespace phoenix = boost::phoenix;
namespace fusion = boost::fusion;
namespace spirit = boost::spirit;
namespace ascii = boost::spirit::ascii;
namespace qi = boost::spirit::qi;

namespace uri { namespace parsers { namespace rules {


template <typename Iterator, typename HostT>
struct host
{
    using rule_type = qi::rule<Iterator, std::string()>;

    host()
    {
        using namespace qi::labels;

        using boost::phoenix::at_c;
        using boost::phoenix::ref;

        // host          =  IP-literal /  IPv4address /  reg-name
        _host            = _IP_literal | _ip.v4()     | _reg_name;

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
    qi::rule<Iterator, HostT()>       _host;
    qi::rule<Iterator, std::string()> _IP_literal;
    qi::rule<Iterator, std::string()> _reg_name;
    qi::rule<Iterator, std::string()> _pct_encoded;
    rules::ip<Iterator> _ip;
    rules::character<Iterator> _char;
};

}}} // namespace uri::parsers::rules

#endif // #define uri__parsers__rules__host_hpp
