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

#include <uri/parsers/rules/character.hpp>
#include <uri/parsers/rules/host.hpp>
#include <uri/parsers/rules/path.hpp>

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
                             >> _path.abempty()[at_c<3>(_val) = _1]
                           )
                         | _path.absolute()[at_c<3>(_val) = _1]
                         | _path.rootless()[at_c<3>(_val) = _1]
                         | _path.empty()[at_c<3>(_val) = _1];

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
        _relative_part   = ( "//" > _authority > _path.abempty() )
                         | _path.absolute()
                         | _path.noscheme()
                         | _path.empty();

        // scheme        = ALPHA           *( ALPHA        /  DIGIT       / "+" / "-" / "." )
        _scheme          = ascii::alpha >> *( ascii::alpha | ascii::digit | ascii::char_("+-.") );

        // authority     = [  userinfo    "@" ]    host    [  ":"   port ]
//            _authority       = -(_userinfo >> '@') >> _host >> -( ':' >> _port );
        _authority       = -(_userinfo >> '@') >> _host() >> -( ':' >> _port );

        // userinfo      = *(  unreserved /  pct-encoded /  sub-delims / ":" )
        _userinfo        = *( _char.unreserved() | _char.percent_encoded() | _char.sub_delims() | ascii::char_(':') );

        // port          = *DIGIT
        _port            = *ascii::digit;

        // query         = *(  pchar / "/" / "?" )
        _query           = *( _char.pchar() | ascii::char_("/?") );

        // fragment      = *(  pchar / "/" / "?" )
        _fragment        = *( _char.pchar() | ascii::char_("/?") );




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
        _path.enable_debug();
//            BOOST_SPIRIT_DEBUG_NODE(_uri_reference);
        BOOST_SPIRIT_DEBUG_NODE(_scheme);
//            BOOST_SPIRIT_DEBUG_NODE(_authority);
        BOOST_SPIRIT_DEBUG_NODE(_userinfo);
        _host.enable_debug();
        BOOST_SPIRIT_DEBUG_NODE(_port);
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
    rules::host<Iterator, std::string> _host;
    qi::rule<Iterator, std::string()> _port;
    rules::path<Iterator>             _path;
    qi::rule<Iterator, std::string()> _query;
    qi::rule<Iterator, std::string()> _fragment;
    rules::character<Iterator> _char;
};

}}} // namespace uri::parsers::grammar

#endif // uri__parsers__grammars__grammar_hpp
