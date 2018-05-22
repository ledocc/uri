#ifndef uri__basic_builder_hpp
#define uri__basic_builder_hpp



#include <string>

#include <uri/basic_uri.hpp>
#include <uri/detail/tags.hpp>



namespace uri {

template <typename TagsT>
struct uri_component
{
    uri_component(const std::string & value)
        : _value(value)
    {}

    std::string _value;
};

using scheme_t   = uri_component<detail::scheme_tag>;
using host_t     = uri_component<detail::host_tag>;
using port_t     = uri_component<detail::port_tag>;
using userinfo_t = uri_component<detail::userinfo_tag>;
using path_t     = uri_component<detail::path_tag>;
using query_t    = uri_component<detail::query_tag>;
using fragment_t = uri_component<detail::fragment_tag>;


inline scheme_t   scheme(const std::string & value)   { return scheme_t(value); }
inline host_t     host(const std::string & value)     { return host_t(value); }
inline port_t     port(const std::string & value)     { return port_t(value); }
inline userinfo_t userinfo(const std::string & value) { return userinfo_t(value); }
inline path_t     path(const std::string & value)     { return path_t(value); }
inline query_t    query(const std::string & value)    { return query_t(value); }
inline fragment_t fragment(const std::string & value) { return fragment_t(value); }


template <typename ProtocolTag>
class basic_builder
{
public:
    using uri_type = basic_uri<ProtocolTag>;

public:
    basic_builder(uri_type & uri): _uri(uri) {}

    basic_builder operator << (const scheme_t &   scheme);
    basic_builder operator << (const userinfo_t & userinfo);
    basic_builder operator << (const host_t &     host);
    basic_builder operator << (const port_t &     port);
    basic_builder operator << (const path_t &     path);
    basic_builder operator << (const query_t &    query);
    basic_builder operator << (const fragment_t & fragment);


private:
    uri_type _uri;
};

} // namespace uri

#endif // uri__basic_builder_hpp
