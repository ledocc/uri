#ifndef uri__algorithm_hpp
#define uri__algorithm_hpp



#include <uri/basic_uri.hpp>
#include <uri/percent/codec.hpp>



namespace uri {

template < typename ProtocolTag >
basic_uri<ProtocolTag> encode(const basic_uri<ProtocolTag> & uri_ )
{
    basic_uri<ProtocolTag> result;

    result.scheme(                    uri_.scheme() );
    result.userinfo(  percent::encode(uri_.userinfo()) );
    result.host(      percent::encode(uri_.host()) );
    result.port(                      uri_.port() );
    result.path(      percent::encode(uri_.path()) );
    result.query(     percent::encode(uri_.query()) );
    result.fragment(  percent::encode(uri_.fragment()) );

    return result;
}

template < typename ProtocolTag >
basic_uri<ProtocolTag> decode(const basic_uri<ProtocolTag> & uri_ )
{
    basic_uri<ProtocolTag> result;

    result.scheme(                    uri_.scheme() );
    result.userinfo(  percent::decode(uri_.userinfo()) );
    result.host(      percent::decode(uri_.host()) );
    result.port(                      uri_.port() );
    result.path(      percent::decode(uri_.path()) );
    result.query(     percent::decode(uri_.query()) );
    result.fragment(  percent::decode(uri_.fragment()) );

    return result;
}

} // namespace uri

#endif // uri__algorithm_hpp
