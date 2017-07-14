#ifndef uri__parsers__rules__fragment_hpp
#define uri__parsers__rules__fragment_hpp



#include <string>

#include <boost/spirit/include/qi.hpp>

#include <uri/parsers/rules/character.hpp>



namespace uri { namespace parsers { namespace rules {

template <typename Iterator>
class fragment
{
public:
    using rule_type = boost::spirit::qi::rule<Iterator, std::string()>;


public:
    fragment()
    {
        namespace ascii = boost::spirit::ascii;


        // fragment      = *(  pchar / "/" / "?" )
        _fragment        = *( _char.pchar() | ascii::char_("/?") );
        _fragment.name("fragment");
    }

    void enable_debug()
    {
        BOOST_SPIRIT_DEBUG_NODE(_fragment);
    }

    const rule_type & operator() () const { return _fragment; }


private:
    rule_type _fragment;
    rules::character<Iterator> _char;
};

}}} // namespace uri::parsers::rules

#endif // uri__parsers__rules__fragment_hpp
