#ifndef uri__parsers__grammars__uri__grammar_hpp
#define uri__parsers__grammars__uri__grammar_hpp



#define BOOST_SPIRIT_DEBUG

#include <string>

#include <boost/fusion/include/std_tuple.hpp>
#include <boost/phoenix/fusion/at.hpp>
#include <boost/phoenix/statement/if.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_optional.hpp>

#include <uri/parsers/rules/uri/character.hpp>

#include <uri/fusion/basic_uri.hpp>
#include <uri/phoenix/basic_uri_accessor.hpp>
#include <uri/traits.hpp>



namespace phoenix = boost::phoenix;
namespace fusion  = boost::fusion;
namespace spirit  = boost::spirit;
namespace ascii   = boost::spirit::ascii;
namespace qi      = boost::spirit::qi;

namespace uri {
namespace parsers {
namespace grammars {
namespace uri {


template < typename Iterator, typename ProtocolTag >
struct grammar : public boost::spirit::qi::grammar< Iterator, basic_uri< ProtocolTag >() >
{
    using protocol_tag = ProtocolTag;
    using uri_type     = basic_uri< protocol_tag >;
    using uri_traits   = ::uri::traits< protocol_tag >;


    grammar()
        : grammar::base_type( _uri_reference, "uri::parser" )
    {
        using namespace qi::labels;
        using boost::phoenix::at_c;
        using boost::phoenix::if_;

        // clang-format off


        // URI           =  scheme   ":"    hier-part   [  "?"    query ]   [  "#"    fragment ]
        _uri             = _scheme()[phoenix::scheme_(_val) = _1]
                         > ':' > _hier_part
                            [
                                phoenix::userinfo_(_val) = at_c<0>(_1),
                                phoenix::host_(_val)     = at_c<1>(_1),
                                phoenix::port_(_val)     = at_c<2>(_1),
                                phoenix::path_(_val)     = at_c<3>(_1)
                            ]
                         > -( '?' > _query()[phoenix::query_(_val) = _1] )
                         > -( '#' > _fragment()[phoenix::fragment_(_val) = _1] );

        // hier-part     = "//"     authority     path-abempty
        //               /  path-absolute
        //               /  path-rootless
        //               /  path-empty
        _hier_part       = ( "//" > _authority
                                         [
                                             if_(at_c<0>(_1))[ at_c<0>(_val) = *at_c<0>(_1) ],
                                                               at_c<1>(_val) = at_c<1>(_1),
                                             if_(at_c<2>(_1))[ at_c<2>(_val) = *at_c<2>(_1) ]
                                         ]
                             > _path.abempty()[at_c<3>(_val) = _1]
                           )
                         | _path.absolute()[at_c<3>(_val) = _1]
                         | _path.rootless()[at_c<3>(_val) = _1]
                         | _path.empty()[at_c<3>(_val) = _1];

        // URI-reference =  URI /  relative-ref
        _uri_reference   = _uri | _relative_ref;

        // absolute-URI  =  scheme    ":"     hier-part    [  "?"     query ]
        _absolute_uri    = _scheme() > ':' > _hier_part > -( '?' > _query() );

        // relative-ref  =  relative-part    [  "?"     query ]    [  "#"     fragment ]
        _relative_ref    = _relative_part > -( '?' > _query() ) > -( '#' > _fragment() );

        // relative-part = "//"     authority     path-abempty
        //               /  path-absolute
        //               /  path-noscheme
        //               /  path-empty
        _relative_part   = ( "//" > _authority > _path.abempty() )
                         | _path.absolute()
                         | _path.noscheme()
                         | _path.empty();

        // authority     = [  userinfo    "@" ]    host    [  ":"   port ]
        _authority       = -( qi::hold[_userinfo() >> '@'] ) >> _host() >> -( ':' > _port() );



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

        // clang-format on
    }

    void enable_debug()
    {
        // BOOST_SPIRIT_DEBUG_NODE(_uri);
        // BOOST_SPIRIT_DEBUG_NODE(_uri_reference);
        BOOST_SPIRIT_DEBUG_NODE( _hier_part );
        BOOST_SPIRIT_DEBUG_NODE( _authority );
        _path.enable_debug();
        _scheme.enable_debug();
        _userinfo.enable_debug();
        _host.enable_debug();
        _port.enable_debug();
        _query.enable_debug();
        _fragment.enable_debug();
        _char.enable_debug();
    }


private:
    qi::rule< Iterator, uri_type() >                                                         _uri;
    qi::rule< Iterator, std::tuple< std::string, std::string, std::string, std::string >() > _hier_part;
    qi::rule< Iterator, uri_type() >                                                         _uri_reference;
    qi::rule< Iterator >                                                                     _absolute_uri;
    qi::rule< Iterator >                                                                     _relative_ref;
    qi::rule< Iterator >                                                                     _relative_part;
    qi::rule< Iterator, std::tuple< boost::optional< std::string >, std::string, boost::optional< std::string > >() >
                                      _authority;
    rules::uri::character< Iterator > _char;

    typename uri_traits::template scheme_parser_rule< Iterator >   _scheme;
    typename uri_traits::template userinfo_parser_rule< Iterator > _userinfo;
    typename uri_traits::template host_parser_rule< Iterator >     _host;
    typename uri_traits::template port_parser_rule< Iterator >     _port;
    typename uri_traits::template path_parser_rule< Iterator >     _path;
    typename uri_traits::template query_parser_rule< Iterator >    _query;
    typename uri_traits::template fragment_parser_rule< Iterator > _fragment;
};

} // namespace uri
} // namespace grammars
} // namespace parsers
} // namespace uri

#endif // uri__parsers__grammars__uri__grammar_hpp
