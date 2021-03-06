#ifndef uri__parsers__rules__uri__ip_hpp
#define uri__parsers__rules__uri__ip_hpp



#include <iostream>
#include <string>

#include <boost/phoenix/core/reference.hpp>
#include <boost/phoenix/fusion/at.hpp>
#include <boost/spirit/include/qi.hpp>

#include <uri/parsers/rules/uri/character.hpp>



namespace uri {
namespace parsers {
namespace rules {
namespace uri {

template < typename Iterator >
class ip
{
public:
    using rule_type = boost::spirit::qi::rule< Iterator, std::string() >;

    // clang-format off
    ip()
    {
        namespace ascii = boost::spirit::ascii;
        namespace qi = boost::spirit::qi;

        using namespace qi::labels;

        using boost::phoenix::at_c;
        using boost::phoenix::ref;

        // IPvFuture     = "v"    1*HEXDIG          "."    1*(  unreserved /  sub-delims / ":" )
        _IPvFuture       = ascii::char_('v') >> +ascii::xdigit >> ascii::char_('.') >> +( _char.unreserved() | _char.sub_delims() | ascii::char_(':') );
        _IPvFuture.name("uri.IPvFuture");

        // IPv6address   =                                                                   6(  h16    ":" )     ls32
        //               /                                                "::"               5(  h16    ":" )     ls32
        //               / [                                     h16 ]    "::"               4(  h16    ":" )     ls32
        //               / [                *1( h16    ":" )     h16 ]    "::"               3(  h16    ":" )     ls32
        //               / [                *2( h16    ":" )     h16 ]    "::"               2(  h16    ":" )     ls32
        //               / [                *3( h16    ":" )     h16 ]    "::"                   h16    ":"       ls32
        //               / [                *4( h16    ":" )     h16 ]    "::"                                    ls32
        //               / [                *5( h16    ":" )     h16 ]    "::"                                    h16
        //               / [                *6( h16    ":" )     h16 ]    "::"
        _IPv6address     %=  qi::hold[ _IPv6address_8   ]
                           | qi::hold[ _IPv6address_0_7 ]
                           | qi::hold[ _IPv6address_1_6 ]
                           | qi::hold[ _IPv6address_2_5 ]
                           | qi::hold[ _IPv6address_3_4 ]
                           | qi::hold[ _IPv6address_4_3 ]
                           | qi::hold[ _IPv6address_5_2 ]
                           | qi::hold[ _IPv6address_6_1 ]
                           | qi::hold[ _IPv6address_7_0 ];
        _IPv6address.name("uri.IPv6address");

        _IPv6address_8   =                                                                                qi::repeat(6)[ _h16_colon ] >> _ls32;
        _IPv6address_0_7 =                                                            qi::string("::") >> qi::repeat(5)[ _h16_colon ] >> _ls32;
        _IPv6address_1_6 = -( _h16                                               ) >> qi::string("::") >> qi::repeat(4)[ _h16_colon ] >> _ls32;
        _IPv6address_2_5 = -( _h16 >> qi::repeat(0, 1)[ qi::hold[ _colon_h16 ] ] ) >> qi::string("::") >> qi::repeat(3)[ _h16_colon ] >> _ls32;
        _IPv6address_3_4 = -( _h16 >> qi::repeat(0, 2)[ qi::hold[ _colon_h16 ] ] ) >> qi::string("::") >> qi::repeat(2)[ _h16_colon ] >> _ls32;
        _IPv6address_4_3 = -( _h16 >> qi::repeat(0, 3)[ qi::hold[ _colon_h16 ] ] ) >> qi::string("::") >>                _h16_colon   >> _ls32;
        _IPv6address_5_2 = -( _h16 >> qi::repeat(0, 4)[ qi::hold[ _colon_h16 ] ] ) >> qi::string("::") >>                                _ls32;
        _IPv6address_6_1 = -( _h16 >> qi::repeat(0, 5)[ qi::hold[ _colon_h16 ] ] ) >> qi::string("::") >>                                _h16 ;
        _IPv6address_7_0 = -( _h16 >> qi::repeat(0, 6)[ qi::hold[ _colon_h16 ] ] ) >> qi::string("::");

        // h16           =            1*4   HEXDIG
        _h16             = qi::repeat(1, 4)[ascii::xdigit];

        // cutom
        _h16_colon       = _h16 >> ascii::char_(':');
        _colon_h16       = ascii::char_(':') >> _h16;

        // ls32          =         (  h16              ":"      h16 ) /  IPv4address
        _ls32            = qi::hold[ _h16 >> qi::char_(':') >> _h16 ] | _IPv4address;

        // IPv4address   =  dec-octet "." dec-octet "." dec-octet "." dec-octet
        _IPv4address     = _dec_octet >> qi::repeat(3)[qi::char_('.') >> _dec_octet];
        _IPv4address.name("uri.IPv4address");

        // dec-octet     = DIGIT                 ; 0-9
        //               / %x31-39 DIGIT         ; 10-99
        //               / "1" 2DIGIT            ; 100-199
        //               / "2" %x30-34 DIGIT     ; 200-249
        //               / "25" %x30-35          ; 250-255
        _dec_octet       = qi::hold[ qi::char_('1') >> ascii::digit >> ascii::digit ]
                         | qi::hold[ qi::char_('2') >> qi::char_('0', '4') >> ascii::digit ]
                         | qi::hold[ qi::char_('2') >> qi::char_('5') >> qi::char_('0', '5') ]
                         | qi::hold[ qi::char_('1', '9') >> ascii::digit ]
                         | ascii::digit;
    }
    // clang-format on

    void enable_debug()
    {
        BOOST_SPIRIT_DEBUG_NODE( _IPvFuture );
        BOOST_SPIRIT_DEBUG_NODE( _IPv6address );
        BOOST_SPIRIT_DEBUG_NODE( _IPv6address_8 );
        BOOST_SPIRIT_DEBUG_NODE( _IPv6address_0_7 );
        BOOST_SPIRIT_DEBUG_NODE( _IPv6address_1_6 );
        BOOST_SPIRIT_DEBUG_NODE( _IPv6address_2_5 );
        BOOST_SPIRIT_DEBUG_NODE( _IPv6address_3_4 );
        BOOST_SPIRIT_DEBUG_NODE( _IPv6address_4_3 );
        BOOST_SPIRIT_DEBUG_NODE( _IPv6address_5_2 );
        BOOST_SPIRIT_DEBUG_NODE( _IPv6address_6_1 );
        BOOST_SPIRIT_DEBUG_NODE( _IPv6address_7_0 );
        BOOST_SPIRIT_DEBUG_NODE( _h16 );
        BOOST_SPIRIT_DEBUG_NODE( _h16_colon );
        BOOST_SPIRIT_DEBUG_NODE( _colon_h16 );
        BOOST_SPIRIT_DEBUG_NODE( _ls32 );
        BOOST_SPIRIT_DEBUG_NODE( _IPv4address );
        BOOST_SPIRIT_DEBUG_NODE( _dec_octet );
        _char.enable_debug();
    }

    const rule_type & v4() const { return _IPv4address; }
    const rule_type & v6() const { return _IPv6address; }
    const rule_type & vFuture() const { return _IPvFuture; }


private:
    rule_type                         _IPvFuture;
    rule_type                         _IPv6address;
    rule_type                         _IPv6address_8;
    rule_type                         _IPv6address_0_7;
    rule_type                         _IPv6address_1_6;
    rule_type                         _IPv6address_2_5;
    rule_type                         _IPv6address_3_4;
    rule_type                         _IPv6address_4_3;
    rule_type                         _IPv6address_5_2;
    rule_type                         _IPv6address_6_1;
    rule_type                         _IPv6address_7_0;
    rule_type                         _h16;
    rule_type                         _h16_colon;
    rule_type                         _colon_h16;
    rule_type                         _ls32;
    rule_type                         _IPv4address;
    rule_type                         _dec_octet;
    rules::uri::character< Iterator > _char;
};

} // namespace uri
} // namespace rules
} // namespace parsers
} // namespace uri

#endif // uri__parsers__rules__uri__ip_hpp
