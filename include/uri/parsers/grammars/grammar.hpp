#ifndef uri__parsers__grammars__grammar_hpp
#define uri__parsers__grammars__grammar_hpp

#define BOOST_SPIRIT_DEBUG

#include <string>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/fusion/include/std_tuple.hpp>

#include <uri/fusion/adapted_basic_uri.hpp>
#include <uri/phoenix/adapted_basic_uri_accessor.hpp>



namespace phoenix = boost::phoenix;
namespace fusion = boost::fusion;
namespace spirit = boost::spirit;
namespace ascii = boost::spirit::ascii;
namespace qi = boost::spirit::qi;

namespace uri { namespace parsers { namespace grammars {


template <typename Iterator, typename UriT>
struct grammar : boost::spirit::qi::grammar<Iterator, UriT()>
{
    grammar() : grammar::base_type(_uri_reference, "uri::parser")
    {
        using namespace qi::labels;

        using boost::phoenix::at_c;
        using boost::phoenix::ref;


        // URI           =  scheme   ":"    hier-part   [  "?"    query ]   [  "#"    fragment ]
//          _uri             = _scheme > ':' > _hier_part > -( '?' > _query ) > -( '#' > _fragment );

        _uri             = _scheme[phoenix::scheme_(_val) = _1]
                         > ':' > _hier_part
                            [
                                phoenix::userinfo_(_val) = at_c<0>(_1),
                                phoenix::host_(_val)     = at_c<1>(_1),
                                phoenix::port_(_val)     = at_c<2>(_1),
                                phoenix::path_(_val)     = at_c<3>(_1)
                            ]
                         > -( '?' > _query[phoenix::query_(_val) = _1] )
                         > -( '#' > _fragment[phoenix::fragment_(_val) = _1] );

        // hier-part     = "//"     authority     path-abempty
        //               /  path-absolute
        //               /  path-rootless
        //               /  path-empty
        _hier_part       = ( "//" > _authority
                                         [
                                             at_c<0>(_val) = at_c<0>(_1),
                                             at_c<1>(_val) = at_c<1>(_1),
                                             at_c<2>(_val) = at_c<2>(_1)
                                         ]
                             >> _path_abempty[at_c<3>(_val) = _1]
                           )
                         | _path_absolute[at_c<3>(_val) = _1]
                         | _path_rootless[at_c<3>(_val) = _1]
                         | _path_empty[at_c<3>(_val) = _1];

        // URI-reference =  URI /  relative-ref
        _uri_reference   = _uri | _relative_ref;

        // absolute-URI  =  scheme    ":"     hier-part    [  "?"     query ]
        _absolute_uri    = _scheme > ':' > _hier_part > -( '?' > _query );

        // relative-ref  =  relative-part    [  "?"     query ]    [  "#"     fragment ]
        _relative_ref    = _relative_part > -( '?' > _query ) > -( '#' > _fragment );

        // relative-part = "//"     authority     path-abempty
        //               /  path-absolute
        //               /  path-noscheme
        //               /  path-empty
        _relative_part   = ( "//" > _authority > _path_abempty )
                         | _path_absolute
                         | _path_noscheme
                         | _path_empty;

        // scheme        = ALPHA           *( ALPHA        /  DIGIT       / "+" / "-" / "." )
        _scheme          = ascii::alpha >> *( ascii::alpha | ascii::digit | ascii::char_("+-.") );

        // authority     = [  userinfo    "@" ]    host    [  ":"   port ]
//            _authority       = -(_userinfo >> '@') >> _host >> -( ':' >> _port );
        _authority       = -(_userinfo >> '@') >> _host >> -( ':' >> _port );

        // userinfo      = *(  unreserved /  pct-encoded /  sub-delims / ":" )
        _userinfo        = *( _unreserved | _pct_encoded | _sub_delims | ascii::char_(':') );

        // host          =  IP-literal /  IPv4address /  reg-name
        _host            = _IP_literal | _IPv4address | _reg_name;

        // port          = *DIGIT
        _port            = *ascii::digit;

        // IP-literal    = "["    (  IPv6address /  IPvFuture )    "]"
        _IP_literal      = ascii::char_('[') >> ( _IPv6address | _IPvFuture ) >> ascii::char_(']');

        // IPvFuture     = "v"    1*HEXDIG          "."    1*(  unreserved /  sub-delims / ":" )
        _IPvFuture       = ascii::char_('v') >> +ascii::xdigit >> ascii::char_('.') >> +( _unreserved | _sub_delims | ascii::char_(':') );

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
        // TODO
        _dec_octet       = ( ascii::digit )
                         | ( qi::char_('1', '9') >> ascii::digit )
                         | ( qi::char_('1') >> ascii::digit >> ascii::digit )
                         | ( qi::char_('2') >> qi::char_('0', '4') >> ascii::digit )
                         | ( qi::char_('2') >> qi::char_('5') >> qi::char_('0', '5') )
                ;
        // reg-name      = *(  unreserved /   pct-encoded /   sub-delims )
        _reg_name        = *( _unreserved | _pct_encoded | _sub_delims );

        // path          =  path-abempty    ; begins with "/" or is empty
        //               /  path-absolute   ; begins with "/" but not "//"
        //               /  path-noscheme   ; begins with a non-colon segment
        //               /  path-rootless   ; begins with a segment
        //               /  path-empty      ; zero characters

        _path            = _path_abempty
                         | _path_absolute
                         | _path_noscheme
                         | _path_rootless
                         | _path_empty;

        // path-abempty  = *( "/"     segment )
        _path_abempty    = *( ascii::char_('/') > _segment );
        // path-absolute = "/"    [   segment-nz    *( "/"     segment ) ]
        _path_absolute   = ascii::char_('/') > -( _segment_nz >> *( ascii::char_('/') >> _segment ) );
        // path-noscheme =  segment-nz-nc    *( "/"     segment )
        _path_noscheme   = _segment_nz_nc > *( ascii::char_('/')>> _segment );
        // path-rootless =  segment-nz    *( "/"     segment )
        _path_rootless   = _segment_nz > *( ascii::char_('/') > _segment );
        // path-empty    = 0<pchar>
        _path_empty      = !_pchar;

        // segment       = * pchar
        _segment         = *_pchar;
        // segment-nz    = 1*pchar
        _segment_nz      = +_pchar;
        // segment-nz-nc = 1*( unreserved /  pct-encoded  / sub-delims /  "@" )
        //                 ; non-zero-length segment without any colon ":"
        _segment_nz_nc   = +( _unreserved | _pct_encoded | _sub_delims | ascii::char_('@') );

        // pchar         =  unreserved /  pct-encoded /  sub-delims / ":" / "@"
        _pchar           = _unreserved | _pct_encoded | _sub_delims | ascii::char_(":@");

        // query         = *(  pchar / "/" / "?" )
        _query           = *( _pchar | ascii::char_("/?") );

        // fragment      = *(  pchar / "/" / "?" )
        _fragment        = *( _pchar | ascii::char_("/?") );

        // pct-encoded   = "%"    HEXDIG           HEXDIG
        _pct_encoded     = ascii::char_('%') >> ascii::xdigit >> ascii::xdigit;

        // unreserved    = ALPHA        / DIGIT /        "-" / "." / "_" /  "~"
        _unreserved      = ascii::alpha | ascii::digit | ascii::char_("-._~");

        // reserved      =  gen-delims /  sub-delims
        _reserved        = _gen_delims | _sub_delims;

        // gen-delims    = ":" / "/" / "?" / "#" / "[" / "]" / "@"
        _gen_delims      = ascii::char_(":/?#[]@");

        // sub-delims    = "!" / "$" / "&" /  "'" / "(" / ")"
        //               / "*" / "+" / "," /  ";" / "="
        _sub_delims      = ascii::char_("!$&\'()*+,;=");



        qi::on_error<qi::fail>
        (
            _uri_reference
          , std::cout
                << boost::phoenix::val("Error! Expecting ")
                << _4                               // what failed?
                << boost::phoenix::val(" here: \"")
                << boost::phoenix::construct<std::string>(_3, _2)   // iterators to error-pos, end
                << boost::phoenix::val("\"")
                << std::endl
        );
    }

    void enable_debug()
    {
        //BOOST_SPIRIT_DEBUG_NODE(_uri);
        BOOST_SPIRIT_DEBUG_NODE(_hier_part);
        BOOST_SPIRIT_DEBUG_NODE(_authority);
        BOOST_SPIRIT_DEBUG_NODE(_path_abempty);
        BOOST_SPIRIT_DEBUG_NODE(_path_absolute);
        BOOST_SPIRIT_DEBUG_NODE(_path_empty);
        BOOST_SPIRIT_DEBUG_NODE(_path_noscheme);
        BOOST_SPIRIT_DEBUG_NODE(_path_rootless);
//            BOOST_SPIRIT_DEBUG_NODE(_uri_reference);
        BOOST_SPIRIT_DEBUG_NODE(_scheme);
//            BOOST_SPIRIT_DEBUG_NODE(_authority);
        BOOST_SPIRIT_DEBUG_NODE(_userinfo);
        BOOST_SPIRIT_DEBUG_NODE(_host);
        BOOST_SPIRIT_DEBUG_NODE(_port);
        BOOST_SPIRIT_DEBUG_NODE(_path);
        BOOST_SPIRIT_DEBUG_NODE(_query);
        BOOST_SPIRIT_DEBUG_NODE(_fragment);
    }



    using uri_type = UriT;

    qi::rule<Iterator, uri_type()> _uri;
    qi::rule<Iterator, std::tuple<std::string, std::string, std::string, std::string>()> _hier_part;
    qi::rule<Iterator, uri_type()> _uri_reference;
    qi::rule<Iterator> _absolute_uri;
    qi::rule<Iterator> _relative_ref;
    qi::rule<Iterator> _relative_part;
    qi::rule<Iterator, std::string()> _scheme;
    qi::rule<Iterator, std::tuple<std::string, std::string, std::string>()> _authority;
    qi::rule<Iterator, std::string()> _userinfo;
    qi::rule<Iterator, std::string()> _host;
    qi::rule<Iterator, std::string()> _port;
    qi::rule<Iterator, std::string()> _IP_literal;
    qi::rule<Iterator, std::string()> _IPvFuture;
    qi::rule<Iterator, std::string()> _IPv6address;
    qi::rule<Iterator, std::string()> _h16;
    qi::rule<Iterator, std::string()> _h16_colon;
    qi::rule<Iterator, std::string()> _ls32;
    qi::rule<Iterator, std::string()> _IPv4address;
    qi::rule<Iterator, std::string()> _dec_octet;
    qi::rule<Iterator, std::string()> _reg_name;
    qi::rule<Iterator, std::string()> _path;
    qi::rule<Iterator, std::string()> _path_abempty;
    qi::rule<Iterator, std::string()> _path_absolute;
    qi::rule<Iterator, std::string()> _path_noscheme;
    qi::rule<Iterator, std::string()> _path_rootless;
    qi::rule<Iterator, std::string()> _path_empty;
    qi::rule<Iterator, std::string()> _segment;
    qi::rule<Iterator, std::string()> _segment_nz;
    qi::rule<Iterator, std::string()> _segment_nz_nc;
    qi::rule<Iterator, std::string()> _pchar;
    qi::rule<Iterator, std::string()> _query;
    qi::rule<Iterator, std::string()> _fragment;
    qi::rule<Iterator, std::string()> _pct_encoded;
    qi::rule<Iterator, char()> _unreserved;
    qi::rule<Iterator, char()> _reserved;
    qi::rule<Iterator, char()> _gen_delims;
    qi::rule<Iterator, char()> _sub_delims;
};

}}} // namespace uri::parsers::grammar

#endif // uri__parsers__grammars__grammar_hpp
