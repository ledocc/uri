#ifndef uri__ios_hpp
#define uri__ios_hpp



#include <ostream>

#include <uri/basic_uri.hpp>



namespace uri {

template <typename ProtocolTag>
std::ostream & operator << (std::ostream & os, const basic_uri<ProtocolTag> & uri)
{
    os << "scheme   = " << uri.scheme()   << "\n"
       << "userinfo = " << uri.userinfo() << "\n"
       << "host     = " << uri.host()     << "\n"
       << "port     = " << uri.port()     << "\n"
       << "path     = " << uri.path()     << "\n"
       << "query    = " << uri.query()    << "\n"
       << "fragment = " << uri.fragment();
    return os;
}

} // namespace uri

#endif // uri__ios_hpp
