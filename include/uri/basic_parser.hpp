#ifndef uri__parser_hpp
#define uri__parser_hpp

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
#include <uri/basic_uri.hpp>
#include <uri/ios.hpp>



namespace phoenix = boost::phoenix;
namespace fusion = boost::fusion;
namespace spirit = boost::spirit;
namespace ascii = boost::spirit::ascii;
namespace qi = boost::spirit::qi;

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
    bool parse(const std::string & uriString)
    {
        typedef grammar<std::string::const_iterator, uri_type > uri_grammar;
        uri_type uriParsed;
        uri_grammar uriGrammer; // Our grammar
        uriGrammer.enable_debug();

        std::string::const_iterator iter = uriString.begin();
        std::string::const_iterator end = uriString.end();
        bool r = boost::spirit::qi::parse(iter, end, uriGrammer, uriParsed);


        std::cout << "try to parse : \""<<uriString << "\""<< std::endl;

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


} // namespace uri

#endif // uri__parser_hpp
