#ifndef uri__parsers__rules__ip_hpp
#define uri__parsers__rules__ip_hpp



#include <string>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/fusion/include/std_tuple.hpp>

#include <uri/parsers/rules/character.hpp>



namespace phoenix = boost::phoenix;
namespace fusion = boost::fusion;
namespace spirit = boost::spirit;
namespace ascii = boost::spirit::ascii;
namespace qi = boost::spirit::qi;

namespace uri { namespace parsers { namespace rules {


template <typename Iterator>
class ip
{
public:
    using rule_string = qi::rule<Iterator, std::string()>;

    ip()
    {
        using namespace qi::labels;

        using boost::phoenix::at_c;
        using boost::phoenix::ref;

        // IPvFuture     = "v"    1*HEXDIG          "."    1*(  unreserved /  sub-delims / ":" )
        _IPvFuture       = ascii::char_('v') >> +ascii::xdigit >> ascii::char_('.') >> +( _char.unreserved() | _char.sub_delims() | ascii::char_(':') );

        // IPv6address   =                                                                   6(  h16    ":" )     ls32
        //               /                                                "::"               5(  h16    ":" )     ls32
        //               / [                                     h16 ]    "::"               4(  h16    ":" )     ls32
        //               / [                *1( h16    ":" )     h16 ]    "::"               3(  h16    ":" )     ls32
        //               / [                *2( h16    ":" )     h16 ]    "::"               2(  h16    ":" )     ls32
        //               / [                *3( h16    ":" )     h16 ]    "::"                   h16    ":"       ls32
        //               / [                *4( h16    ":" )     h16 ]    "::"                                    ls32
        //               / [                *5( h16    ":" )     h16 ]    "::"                                    h16
        //               / [                *6( h16    ":" )     h16 ]    "::"
        _IPv6address     = (                                                                    qi::repeat(6)[ _h16_colon ] >> _ls32 )
                         | (                                                qi::string("::") >> qi::repeat(5)[ _h16_colon ] >> _ls32 )
                         | ( -(                                   _h16 ) >> qi::string("::") >> qi::repeat(4)[ _h16_colon ] >> _ls32 )
                         | ( -( qi::repeat(0, 1)[ _h16_colon ] >> _h16 ) >> qi::string("::") >> qi::repeat(3)[ _h16_colon ] >> _ls32 )
                         | ( -( qi::repeat(0, 2)[ _h16_colon ] >> _h16 ) >> qi::string("::") >> qi::repeat(2)[ _h16_colon ] >> _ls32 )
                         | ( -( qi::repeat(0, 3)[ _h16_colon ] >> _h16 ) >> qi::string("::") >>                _h16_colon   >> _ls32 )
                         | ( -( qi::repeat(0, 5)[ _h16_colon ] >> _h16 ) >> qi::string("::") >>                                _ls32 )
                         | ( -( qi::repeat(0, 4)[ _h16_colon ] >> _h16 ) >> qi::string("::") >>                                _h16  )
                         | ( -( qi::repeat(0, 6)[ _h16_colon ] >> _h16 ) >> qi::string("::")                                         );

        // h16           =            1*4   HEXDIG
        _h16             = qi::repeat(1, 4)[ascii::xdigit];

        // cutom
        _h16_colon       = _h16 >> ascii::char_(':');

        // ls32          = (  h16              ":"      h16 ) /  IPv4address
        _ls32            = ( _h16 >> qi::char_(':') >> _h16 ) | _IPv4address;

        // IPv4address   =  dec-octet "." dec-octet "." dec-octet "." dec-octet
        _IPv4address     = _dec_octet >> qi::repeat(3)[qi::char_('.') >> _dec_octet];

        // dec-octet     = DIGIT                 ; 0-9
        //               / %x31-39 DIGIT         ; 10-99
        //               / "1" 2DIGIT            ; 100-199
        //               / "2" %x30-34 DIGIT     ; 200-249
        //               / "25" %x30-35          ; 250-255
        _dec_octet       = ( ascii::digit )
                         | ( qi::char_('1', '9') >> ascii::digit )
                         | ( qi::char_('1') >> ascii::digit >> ascii::digit )
                         | ( qi::char_('2') >> qi::char_('0', '4') >> ascii::digit )
                         | ( qi::char_('2') >> qi::char_('5') >> qi::char_('0', '5') );

    }

    void enable_debug()
    {
        BOOST_SPIRIT_DEBUG_NODE(_IPv4address);
        BOOST_SPIRIT_DEBUG_NODE(_IPv6address);
        BOOST_SPIRIT_DEBUG_NODE(_IPvFuture);
    }

    const rule_string & v4() const      { return _IPv4address; }
    const rule_string & v6() const      { return _IPv6address; }
    const rule_string & vFuture() const { return _IPvFuture; }


private:
    rule_string _IPvFuture;
    rule_string _IPv6address;
    rule_string _h16;
    rule_string _h16_colon;
    rule_string _ls32;
    rule_string _IPv4address;
    rule_string _dec_octet;
    rules::character<Iterator> _char;
};

}}} // namespace uri::parsers::rules

#endif // #define uri__parsers__rules__host_hpp
