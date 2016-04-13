#ifndef uri__percent__codec_h
#define uri__percent__codec_h



#include <uri/percent/code.hpp>



namespace uri { namespace percent {


namespace detail {

///
/// \brief The Hexadecimal2Decimal class is an helper to convert hexadecimal to decimal
///
class Hexadecimal2Decimal
{
    using array_type = std::array<char, 255>;

public:
    Hexadecimal2Decimal()
    {
        char v = 0;
        std::generate(_array.begin()+'0', _array.begin()+'9'+1, [&v]() { return v++; });

        v = 10;
        std::generate(_array.begin()+'A', _array.begin()+'G', [&v]() { return v++; });

        v = 10;
        std::generate(_array.begin()+'a', _array.begin()+'g', [&v]() { return v++; });
    }
    char operator[] (unsigned int index) const { return _array[index]; }


private:
    array_type _array = array_type{ -1 };
};

} // namespace detail


///
/// \brief decode convert a percent encode value to its char representation
/// \param code the percent code to decode
/// \return te decode char
///
char decode(const code & code)
{
    static detail::Hexadecimal2Decimal hexadecimal2Decimal;

    return (hexadecimal2Decimal[ code[1] ] << 4) +
            hexadecimal2Decimal[ code[2] ];

}

///
/// \brief encode convert a char in its percent encoded representation
/// \param c the char to encode
/// \param code is the encoded representation of "c"
///
void encode(char c, code & code)
{
    static std::array<char, 16> decimal2Hexadecimal = { '0', '1', '2', '3', '4', '5', '6', '7',
                                                        '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
    code[0] = '%';
    code[1] = decimal2Hexadecimal[ c >> 4 ];
    code[2] = decimal2Hexadecimal[ c & 0x0F ];
}

}} // namespace uri::percent

#endif // uri__percent__codec_h
