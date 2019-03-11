#ifndef uri__algorithm_hpp
#define uri__algorithm_hpp



#include <uri/basic_uri.hpp>
#include <uri/error.hpp>
#include <uri/parsers/grammars/uri/grammar.hpp>
#include <uri/traits.hpp>

#include <boost/spirit/include/qi_parse.hpp>


namespace uri {

template < typename ProtocolTag, typename StringT, typename StringIteratorT = typename StringT::const_iterator >
basic_uri< ProtocolTag > parse( const StringT & encoded_string, std::error_code & ec, StringIteratorT & last_position )
{
    basic_uri< ProtocolTag >                                        uri;
    parsers::grammars::uri::grammar< StringIteratorT, ProtocolTag > grammar;
    grammar.enable_debug();

    ec.clear();


    auto iter = std::begin( encoded_string );
    auto end  = std::end( encoded_string );

    bool result   = boost::spirit::qi::parse( iter, end, grammar >> boost::spirit::qi::eoi, uri );
    last_position = iter;

    if ( not result )
    {
        ec = make_error_code( error::ParserFailed );
        return basic_uri< ProtocolTag >{};
    }

    if ( iter != end )
    {
        ec = make_error_code( error::ParserFinishBeforeEndOfUri );
        return basic_uri< ProtocolTag >{};
    }

    return uri;
}

//--------------------------------------------------------------------------------------------------------------------//

template < typename ProtocolTag, typename StringT >
basic_uri< ProtocolTag > parse( const StringT & encoded_string )
{
    std::error_code                  ec;
    typename StringT::const_iterator last_position;

    auto uri = parse< ProtocolTag >( encoded_string, ec, last_position );

    if ( ec ) { throw std::system_error( ec ); }
    return uri;
}

} // namespace uri

#endif // uri__algorithm_hpp
