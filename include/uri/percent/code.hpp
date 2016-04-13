#ifndef uri__percent__code_h
#define uri__percent__code_h



#include <array>



namespace uri { namespace percent {

///
/// \brief The code class is 3 char that is the hexa decimal code of a char
///
class code
{
public:
    ///
    /// \brief default constructor initialise the 3 value to 0
    ///
    code() : _code{0} {}

    ///
    /// \brief code constructor from char*
    /// \param code_ the source used to initialize the 3 char store in code
    /// \pre code_ should have a size >= 3
    code(const char * code_)
    {
        _code[0] = code_[0];
        _code[1] = code_[1];
        _code[2] = code_[2];
    }

    ///
    /// \brief operator [] to get a copy of a char
    /// \param index of the char to access
    /// \return a copy of the char with index = "index"
    ///
    char   operator[] (unsigned int index) const { return _code[index]; }

    ///
    /// \brief operator [] to get a reference to a char
    /// \param index of the char to access
    /// \return a reference of the char with index = "index"
    ///
    char & operator[] (unsigned int index)       { return _code[index]; }


private:
    std::array<char, 3> _code;
};

}} // namespace uri::percent

#endif // uri__percent__code_h
