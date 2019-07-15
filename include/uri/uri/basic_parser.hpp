#ifndef uri__parser_hpp
#define uri__parser_hpp



//#define BOOST_SPIRIT_DEBUG

#include <string>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/fusion/include/std_tuple.hpp>

#include <uri/fusion/uri/adapted_basic_uri.hpp>
#include <uri/phoenix/uri/adapted_basic_uri_accessor.hpp>
#include <uri/schemes/uri.hpp>
#include <uri/ios.hpp>



namespace uri {

///
/// \brief The basic_parser class parse an uri encoded string and extract components
///
template <typename ProtocolTag>
class basic_parser
{
public:
    using protocol_tag = ProtocolTag;
    using uri_type = basic_uri<protocol_tag>;


public:
    uri_type operator() ( const std::string & uriString )
    {
        typedef boost::spirit::grammar< std::string::const_iterator, uri_type > uri_grammar;

        uri_grammar uriGrammer;
        uriGrammer.enable_debug();

        std::string::const_iterator iter = uriString.begin();
        std::string::const_iterator end = uriString.end();

        uri_type result;
        bool r = boost::spirit::qi::parse(iter, end, uriGrammer, uriParsed);

        if (r && iter == end)
        {
            std::cout << "-------------------------\n";
            std::cout << "Parsing succeeded\n";
            std::cout << "-------------------------\n";
            std::cout << uriParsed << std::endl;
            return 0;
        }
        else
        {
            std::string::const_iterator some = iter+30;
            std::string context(iter, (some>end)?end:some);
            std::cout << "-------------------------\n";
            std::cout << "Parsing failed\n";
            std::cout << "stopped at: : \"" << context << "\" ...\n";
            std::cout << "-------------------------\n";
            return 1;
        }
    }
};




template <typename StringT, typename GrammarT, typename StorageT>
class parser
{
private:
    using string_type = StringT;
    using string_const_iterator = decltype( std::cbegin( std::declval<string_type>() ) );


public:

    using string_iterator_range = boost::range::iterator_range< string_const_iterator >;
    using

    std::pair<bool, string_iterator_range>
    operator() ( const StringT & string, const GrammarT & grammar, Storage & storage )
    {
        auto iter = std::cbegin( string );
        auto end  = std::cend( string );

        bool result = boost::spirit::qi::parse(iter, end, grammer, storage);

        return { result, { iter, end } };
    }
};

} // namespace uri

#endif // uri__parser_hpp
