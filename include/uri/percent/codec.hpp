#ifndef uri__percent__codec_h
#define uri__percent__codec_h



#include <uri/percent/code.hpp>

#include <algorithm>



namespace uri {
namespace percent {

namespace detail {

///
/// \brief The Hexadecimal2Decimal class is an helper to convert hexadecimal to decimal
///
class Hexadecimal2Decimal
{
    using array_type = std::array< char, 255 >;

public:
    Hexadecimal2Decimal()
    {
        char v = 0;
        std::generate( _array.begin() + static_cast< std::size_t >( '0' ),
                       _array.begin() + static_cast< std::size_t >( '9' ) + 1,
                       [&v]() { return v++; } );

        v = 10;
        std::generate( _array.begin() + static_cast< std::size_t >( 'A' ),
                       _array.begin() + static_cast< std::size_t >( 'G' ),
                       [&v]() { return v++; } );

        v = 10;
        std::generate( _array.begin() + static_cast< std::size_t >( 'a' ),
                       _array.begin() + static_cast< std::size_t >( 'g' ),
                       [&v]() { return v++; } );
    }
    char operator[]( std::size_t index ) const { return _array[index]; }


private:
    array_type _array = array_type{ { -1 } };
};

char hexadecimal2Decimal( char c )
{
    static detail::Hexadecimal2Decimal s_hexadecimal2Decimal;
    return s_hexadecimal2Decimal[static_cast< std::size_t >( c )];
}

char decimal2Hexadecimal( char c )
{
    static std::array< char, 16 > decimal2Hexadecimal_ = {
        { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' }
    };
    return decimal2Hexadecimal_[static_cast< std::size_t >( c )];
}


} // namespace detail


///
/// \brief decode convert a percent encode value to its char representation
/// \param code the percent code to decode
/// \return te decode char
///
char decode( const code & code )
{
    return static_cast< char >( detail::hexadecimal2Decimal( code[1] ) << 4 ) + detail::hexadecimal2Decimal( code[2] );
}


template < typename IteratorT, typename OutputIterator >
void decode( IteratorT begin, IteratorT end, OutputIterator output )
{
    auto it = begin;

    while ( it != end )
    {
        char c = *it;
        ++it;

        if ( '%' == c )
        {
            if ( std::distance( it, end ) < 2 ) { throw std::runtime_error( "uri : percent code not complet" ); }

            char c1 = *( it++ );
            char c2 = *( it++ );

            c = decode( code( c1, c2 ) );
        }

        output = c;
    }
}

std::string decode( const std::string & input_ )
{
    std::string result;
    decode( std::begin( input_ ), std::end( input_ ), std::back_inserter( result ) );
    return result;
}



namespace detail {

struct UnreservedCharacterPolicy
{
    bool operator()( char c ) const
    {
        return !( ( ( 'a' <= c ) && ( c <= 'z' ) ) || ( ( 'A' <= c ) && ( c <= 'Z' ) )
                  || ( ( '0' <= c ) && ( c <= '9' ) ) || ( c == '-' ) || ( c == '.' ) || ( c == '_' ) || ( c == '~' ) );
    }
};

} // namespace detail


///
/// \brief encode convert a char in its percent encoded representation
/// \param c the char to encode
/// \param code is the encoded representation of "c"
///
void encode( char c, code & code )
{
    code[0] = '%';
    code[1] = detail::decimal2Hexadecimal( c >> 4 );
    code[2] = detail::decimal2Hexadecimal( c & 0x0F );
}

template < typename OutputIterator >
void encode( char c, OutputIterator & output )
{
    output = '%';
    output = detail::decimal2Hexadecimal( c >> 4 );
    output = detail::decimal2Hexadecimal( c & 0x0F );
}


template < typename IteratorT, typename OutputIterator, typename CharacterPolicy = detail::UnreservedCharacterPolicy >
void encode( IteratorT               begin,
             IteratorT               end,
             OutputIterator          output,
             const CharacterPolicy & charPolicy = detail::UnreservedCharacterPolicy() )
{
    auto it = begin;

    while ( it != end )
    {
        char c = *it;
        ++it;

        if ( charPolicy( c ) ) { encode( c, output ); }
        else
        {
            output = c;
        }
    }
}

template < typename CharacterPolicy = detail::UnreservedCharacterPolicy >
std::string encode( const std::string &     input_,
                    const CharacterPolicy & charPolicy = detail::UnreservedCharacterPolicy() )
{
    std::string result;
    encode( std::begin( input_ ), std::end( input_ ), std::back_inserter( result ), charPolicy );
    return result;
}

} // namespace percent
} // namespace uri

#endif // uri__percent__codec_h
