#ifndef uri__parsers__rules__port_hpp
#define uri__parsers__rules__port_hpp



#include <string>

#include <boost/spirit/include/qi.hpp>



namespace uri { namespace parsers { namespace rules {

template <typename Iterator>
class port
{
public:
    using rule_type = boost::spirit::qi::rule<Iterator, std::string()>;


public:
    port()
    {
        namespace ascii = boost::spirit::ascii;


        // port          = *DIGIT
        _port            = *ascii::digit;
    }

    void enable_debug()
    {
        BOOST_SPIRIT_DEBUG_NODE(_port);
    }

    const rule_type & operator() () const { return _port; }


private:
    rule_type _port;
};

}}} // namespace uri::parsers::rules

#endif // uri__parsers__rules__port_hpp
