#ifndef uri__fusion__adapted_basic_uri_hpp
#define uri__fusion__adapted_basic_uri_hpp



#include <boost/fusion/adapted/adt/adapt_adt.hpp>

#include <uri/basic_uri.hpp>



BOOST_FUSION_ADAPT_TPL_ADT(
        (ProtocolT),
        (uri::basic_uri)(ProtocolT),
        (std::string const &, std::string const &, obj.scheme()  , obj.scheme(val))
        (std::string const &, std::string const &, obj.userinfo(), obj.userinfo(val))
        (std::string const &, std::string const &, obj.host()    , obj.host(val))
        (std::string const &, std::string const &, obj.port()    , obj.port(val))
        (std::string const &, std::string const &, obj.path()    , obj.path(val))
        (std::string const &, std::string const &, obj.query()   , obj.query(val))
        (std::string const &, std::string const &, obj.fragment(), obj.fragment(val))
        )

#endif // uri__fusion__adapted_basic_uri_hpp
