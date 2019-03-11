#ifndef uri__io_hpp
#define uri__io_hpp



#include <uri/basic_uri.hpp>

#include <ostream>



namespace uri {

template < typename ProtocolTag >
std::ostream & operator<<( std::ostream & os, const basic_uri< ProtocolTag > & uri )
{
    // clang-format off

    os << "basic_uri{ scheme{ " << uri.scheme()
       << " }, userinfo{ "      << uri.userinfo()
       << " }, host{ "          << uri.host()
       << " }, port{ "          << uri.port()
       << " }, path{ "          << uri.path()
       << " }, query{ "         << uri.query()
       << " }, fragment{ "      << uri.fragment()
       << " },  }";

    // clang-format on

    return os;
}

} // namespace uri

#endif // uri__io_hpp
