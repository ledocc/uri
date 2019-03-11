#ifndef uri__phoenix__adapted_basic_uri_accessor_hpp
#define uri__phoenix__adapted_basic_uri_accessor_hpp



#include <boost/phoenix/fusion/at.hpp>



namespace uri {
namespace phoenix {
//namespace {
//    enum index
//    {
//        scheme   = 0,
//        userinfo = 1,
//        host     = 2,
//        port     = 3,
//        path     = 4,
//        query    = 5,
//        fragment = 6
//    };
//} // namespace

    template <typename ArgT>
    decltype(auto)
    scheme_(const ArgT & arg)
    { return boost::phoenix::at_c<0>(arg); }

    template <typename ArgT>
    decltype(auto)
    userinfo_(const ArgT & arg)
    { return boost::phoenix::at_c<1>(arg); }

    template <typename ArgT>
    decltype(auto)
    host_(const ArgT & arg)
    { return boost::phoenix::at_c<2>(arg); }

    template <typename ArgT>
    decltype(auto)
    port_(const ArgT & arg)
    { return boost::phoenix::at_c<3>(arg); }

    template <typename ArgT>
    decltype(auto)
    path_(const ArgT & arg)
    { return boost::phoenix::at_c<4>(arg); }

    template <typename ArgT>
    decltype(auto)
    query_(const ArgT & arg)
    { return boost::phoenix::at_c<5>(arg); }

    template <typename ArgT>
    decltype(auto)
    fragment_(const ArgT & arg)
    { return boost::phoenix::at_c<6>(arg); }


} // namespace phoenix
} // namespace uri


#endif // uri__phoenix__adapted_basic_uri_accessor_hpp
