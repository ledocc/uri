#ifndef uri__traits_hpp
#define uri__traits_hpp



#include <string>



namespace uri {

template <class UriT>
struct traits
{
    using scheme_type   = std::string;
    using userinfo_type = std::string;
    using host_type     = std::string;
    using port_type     = std::string;
    using path_type     = std::string;
    using query_type    = std::string;
    using fragment_type = std::string;
};

} // namespace uri

#endif // uri__traits_hpp
