#ifndef uri__parsers__rules__query_hpp
#define uri__parsers__rules__query_hpp



#include <string>

#include <boost/spirit/include/qi.hpp>

#include <uri/parsers/rules/character.hpp>



namespace uri { namespace parsers { namespace rules {

template <typename Iterator>
class query
{
public:
    using rule_type = boost::spirit::qi::rule<Iterator, std::string()>;


public:
    query()
    {
        namespace ascii = boost::spirit::ascii;


        // query         = *(  pchar / "/" / "?" )
        _query           = *( _char.pchar() | ascii::char_("/?") );
    }

    void enable_debug()
    {
        BOOST_SPIRIT_DEBUG_NODE(_query);
    }

    const rule_type & operator() () const { return _query; }


private:
    rule_type _query;
    rules::character<Iterator> _char;
};

}}} // namespace uri::parsers::rules

#endif // uri__parsers__rules__query_hpp
