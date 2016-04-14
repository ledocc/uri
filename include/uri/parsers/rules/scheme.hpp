#ifndef uri__parsers__rules__scheme_hpp
#define uri__parsers__rules__scheme_hpp



#include <string>

#include <boost/spirit/include/qi.hpp>



namespace uri { namespace parsers { namespace rules {

template <typename Iterator>
class scheme
{
public:
    using rule_type = boost::spirit::qi::rule<Iterator, std::string()>;


public:
    scheme()
    {
        namespace ascii = boost::spirit::ascii;


        // scheme        = ALPHA           *( ALPHA        /  DIGIT       / "+" / "-" / "." )
        _scheme          = ascii::alpha >> *( ascii::alpha | ascii::digit | ascii::char_("+-.") );
    }

    void enable_debug()
    {
        BOOST_SPIRIT_DEBUG_NODE(_scheme);
    }

    const rule_type & operator() () const { return _scheme; }


private:
    rule_type _scheme;
};

}}} // namespace uri::parsers::rules

#endif // uri__parsers__rules__scheme_hpp
