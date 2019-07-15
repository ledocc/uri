#ifndef uri__parsers__test__test_parser_hpp
#define uri__parsers__test__test_parser_hpp



#include <boost/spirit/include/qi_parse.hpp>

#include <string>



namespace uri {
namespace parsers {
namespace test {

template < typename Expr >
void test_string_parser( const std::string & src, Expr const & expr, bool expectedResult )
{
    auto first = src.begin();
    auto last  = src.end();

    std::string result;
    bool        parseResult = boost::spirit::qi::parse( first, last, expr, result );
    BOOST_TEST( ( parseResult && ( first == last ) && ( result == src ) ) == expectedResult );
}

//--------------------------------------------------------------------------------------------------------------------//

template < typename Expr >
void test_char_parser( char src, Expr const & expr, bool expectedResult )
{
    test_string_parser( std::string{ src }, expr, expectedResult );
}

} // namespace test
} // namespace parsers
} // namespace uri

#endif // uri__parsers__test__test_parser_hpp
