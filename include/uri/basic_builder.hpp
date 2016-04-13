#ifndef uri__basic_builder_hpp
#define uri__basic_builder_hpp



#include <uri/basic_uri.hpp>



namespace uri {

template <typename ProtocolTag>
class basic_builder
{
public:
    using uri_type = basic_uri<ProtocolTag>;

public:
    basic_builder(uri_type & uri): _uri(uri) {}

    basic_builder operator << (const uri_type::scheme_type &   scheme);
    basic_builder operator << (const uri_type::userinfo_type & userinfo);
    basic_builder operator << (const uri_type::host_type &     host);
    basic_builder operator << (const uri_type::port_type &     port);
    basic_builder operator << (const uri_type::path_type &     path);
    basic_builder operator << (const uri_type::query_type &    query);
    basic_builder operator << (const uri_type::fragment_type & fragment);


private:
    uri_type _uri;
};

} // namespace uri

#endif // uri__basic_builder_hpp
