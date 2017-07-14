#ifndef uri__parsers__rules__userinfo_hpp
#define uri__parsers__rules__userinfo_hpp



#include <string>

#include <boost/spirit/include/qi.hpp>

#include <uri/parsers/rules/character.hpp>



namespace uri { namespace parsers { namespace rules {

template <typename Iterator>
class userinfo
{
public:
    using rule_type = boost::spirit::qi::rule<Iterator, std::string()>;
//    using rule_type = qi::rule<Iterator, std::tuple<std::string, std::string>() >;

public:
    userinfo()
    {
        namespace ascii = boost::spirit::ascii;


        // userinfo      = *(  unreserved /  pct-encoded /  sub-delims / ":" )
        _userinfo        = *( _char.unreserved() | _char.percent_encoded() | _char.sub_delims() | ascii::char_(':') );
        _userinfo.name("userinfo");

//        _userinfo        = _word >> ':' >> _word;
//        _word            = *( _char.unreserved() | _char.percent_encoded() | _char.sub_delims() );
    }

    void enable_debug()
    {
        BOOST_SPIRIT_DEBUG_NODE(_userinfo);
    }

    const rule_type & operator() () const { return _userinfo; }


private:
//    rule_type _userinfo;
//    qi::rule<Iterator, std::string() > _word;
    rule_type _userinfo;
    rules::character<Iterator> _char;
};

}}} // namespace uri::parsers::rules

#endif // #define uri__parsers__rules__userinfo_hpp
