#ifndef uri__parsers__rules__http__key_value_query_hpp
#define uri__parsers__rules__http__key_value_query_hpp



#include <string>

#include <boost/spirit/include/qi.hpp>

#include <uri/parsers/rules/uri/character.hpp>



namespace uri { namespace parsers { namespace rules {

template <typename Iterator>
class key_value_query
{
public:
    using rule_type = boost::spirit::qi::rule<Iterator, std::string()>;


public:
    key_value_query(char key_value_delimiter_ = '=', char pair_delimiter_ = '&')
    {
        namespace ascii = boost::spirit::ascii;

        _key_value_char = _char.unreserved() | _char.percent_encoded();

        _key_value_pair = +( _key_value_char ) >> ascii::char_(key_value_delimiter_) >> +( _key_value_char );

        _key_value_query = _key_value_pair >> *(pair_delimiter_ >> _key_value_pair);
        _key_value_query.name("http.key_value_query");
    }

    void enable_debug()
    {
        BOOST_SPIRIT_DEBUG_NODE(_key_value_query);
    }

    const rule_type & operator() () const { return _key_value_query; }


private:
    rule_type _key_value_char;
    rule_type _key_value_pair;
    rule_type _key_value_query;
    rules::uri::character<Iterator> _char;
};

}}} // namespace uri::parsers::rules

#endif // uri__parsers__rules__http__key_value_query_hpp
