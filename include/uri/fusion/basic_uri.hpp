#ifndef uri__fusion__adapted_basic_uri_hpp
#define uri__fusion__adapted_basic_uri_hpp



#include <boost/fusion/adapted/adt/adapt_adt.hpp>

#include <uri/basic_uri.hpp>


// clang-format off
BOOST_FUSION_ADAPT_TPL_ADT(
        (ProtocolT),
        (uri::basic_uri)(ProtocolT),
        (typename uri::traits<ProtocolT>::scheme_accessor_return_type,   typename uri::traits<ProtocolT>::scheme_modificator_param_type,   obj.scheme(),   obj.scheme(val))
        (typename uri::traits<ProtocolT>::userinfo_accessor_return_type, typename uri::traits<ProtocolT>::userinfo_modificator_param_type, obj.userinfo(), obj.userinfo(val))
        (typename uri::traits<ProtocolT>::host_accessor_return_type,     typename uri::traits<ProtocolT>::host_modificator_param_type,     obj.host()    , obj.host(val))
        (typename uri::traits<ProtocolT>::port_accessor_return_type,     typename uri::traits<ProtocolT>::port_modificator_param_type,     obj.port()    , obj.port(val))
        (typename uri::traits<ProtocolT>::path_accessor_return_type,     typename uri::traits<ProtocolT>::path_modificator_param_type,     obj.path()    , obj.path(val))
        (typename uri::traits<ProtocolT>::query_accessor_return_type,    typename uri::traits<ProtocolT>::query_modificator_param_type,    obj.query()   , obj.query(val))
        (typename uri::traits<ProtocolT>::fragment_accessor_return_type, typename uri::traits<ProtocolT>::fragment_modificator_param_type, obj.fragment(), obj.fragment(val))
        )
// clang-format on

#endif // uri__fusion__adapted_basic_uri_hpp
