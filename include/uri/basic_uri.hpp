#ifndef uri__basic_uri_hpp
#define uri__basic_uri_hpp



#include <uri/traits.hpp>

#include <boost/utility/string_view.hpp>



namespace uri {

template < typename ProtocolTag >
class basic_uri
{
public:
    using protocol_tag = ProtocolTag;

    using this_type   = basic_uri< protocol_tag >;
    using traits_type = traits< protocol_tag >;

    using scheme_type   = typename traits_type::scheme_type;
    using userinfo_type = typename traits_type::userinfo_type;
    using host_type     = typename traits_type::host_type;
    using port_type     = typename traits_type::port_type;
    using path_type     = typename traits_type::path_type;
    using query_type    = typename traits_type::query_type;
    using fragment_type = typename traits_type::fragment_type;


public:
    basic_uri() = default;

    basic_uri( const scheme_type &   scheme_,
               const userinfo_type & userinfo_,
               const host_type &     host_,
               const port_type &     port_,
               const path_type &     path_,
               const query_type &    query_,
               const fragment_type & fragment_ )
        : _scheme( scheme_ )
        , _userinfo( userinfo_ )
        , _host( host_ )
        , _port( port_ )
        , _path( path_ )
        , _query( query_ )
        , _fragment( fragment_ )
    {}


    bool operator==( const basic_uri & other ) const
    {
        // clang-format off
        return     ( _scheme == other._scheme )
                && ( _userinfo == other._userinfo )
                && ( _host == other._host )
                && ( _port == other._port )
                && ( _path == other._path )
                && ( _query == other._query )
                && ( _fragment == other._fragment );
        // clang-format on
    }


    // Accessor
    const scheme_type &   scheme() const { return _scheme; }
    const userinfo_type & userinfo() const { return _userinfo; }
    const host_type &     host() const { return _host; }
    const port_type &     port() const { return _port; }
    const path_type &     path() const { return _path; }
    const query_type &    query() const { return _query; }
    const fragment_type & fragment() const { return _fragment; }


    // Modifier
    void scheme( const scheme_type & scheme_ ) { _scheme = scheme_; }
    void userinfo( const userinfo_type & userinfo_ ) { _userinfo = userinfo_; }
    void host( const host_type & host_ ) { _host = host_; }
    void port( const port_type & port_ ) { _port = port_; }
    void path( const path_type & path_ ) { _path = path_; }
    void query( const query_type & query_ ) { _query = query_; }
    void fragment( const fragment_type & fragment_ ) { _fragment = fragment_; }


    std::string to_string() const;


private:
    scheme_type   _scheme;
    userinfo_type _userinfo;
    host_type     _host;
    port_type     _port;
    path_type     _path;
    query_type    _query;
    fragment_type _fragment;
};



// template <typename ProtocolTag, typename Allocator>
// std::string generate( const basic_uri<ProtocolTag, Allocator> & uri )
//{
//    typename traits< basic_uri< ProtocolTag, Allocator >::generator_type generator;
//    return generator.apply(uri)
//}

// template <typename URI>
// URI parse( const std::string & encoded_uri_string )
//{
//    typename traits<URI>::parser_type parser;
//    return parser.apply(encoded_uri_string)
//}

} // namespace uri

#endif // uri__basic_uri_hpp
