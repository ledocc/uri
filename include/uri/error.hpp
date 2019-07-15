#ifndef uri__error_hpp
#define uri__error_hpp



#include <system_error>



namespace uri {

enum class error
{
    ParserFailed,
    ParserFinishBeforeEndOfUri
};

} // namespace unoHTTP

//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//

namespace std {
template <>
struct is_error_code_enum< uri::error > : true_type
{};
} // namespace std

//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//

namespace uri {

class error_category : public std::error_category
{
public:
    virtual ~error_category() = default;

    virtual const char * name() const noexcept override;
    virtual std::string  message( int condition ) const override;
};

//--------------------------------------------------------------------------------------------------------------------//

const char * error_category::name() const noexcept
{
    return "uri.error";
}

//--------------------------------------------------------------------------------------------------------------------//

std::string error_category::message( int condition ) const
{
    // clang-format off
    switch ( static_cast< error >( condition ) )
    {
        case error::ParserFailed : return "parser failed";
        case error::ParserFinishBeforeEndOfUri: return "parser finish before end of uri";
    };
    // clang-format on

    return "unknown uri.error";
}

//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//

const std::error_category & get_error_category()
{
    static error_category s_instance;
    return s_instance;
}

//--------------------------------------------------------------------------------------------------------------------//

std::error_code make_error_code( error error )
{
    return std::error_code( static_cast< int >( error ), get_error_category() );
}

} // namespace uri

#endif // uri__error_hpp
