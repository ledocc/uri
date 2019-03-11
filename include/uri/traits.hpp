#ifndef uri__traits_hpp
#define uri__traits_hpp



#include <string>



namespace uri {

template < class UriT >
struct traits
{
    //    using scheme_type                   = implementation_detail;
    //    using scheme_accessor_return_type   = implementation_detail;
    //    using scheme_modificator_param_type = implementation_detail;
    //    using scheme_parser_rule            = implementation_detail;

    //    using userinfo_type                   = implementation_detail;
    //    using userinfo_accessor_return_type   = implementation_detail;
    //    using userinfo_modificator_param_type = implementation_detail;
    //    using userinfo_parser_rule            = implementation_detail;

    //    using host_type                   = implementation_detail;
    //    using host_accessor_return_type   = implementation_detail;
    //    using host_modificator_param_type = implementation_detail;
    //    using host_parser_rule            = implementation_detail;

    //    using port_type                   = implementation_detail;
    //    using port_accessor_return_type   = implementation_detail;
    //    using port_modificator_param_type = implementation_detail;
    //    using port_parser_rule            = implementation_detail;

    //    using path_type                   = implementation_detail;
    //    using path_accessor_return_type   = implementation_detail;
    //    using path_modificator_param_type = implementation_detail;
    //    using path_parser_rule            = implementation_detail;

    //    using query_type                   = implementation_detail;
    //    using query_accessor_return_type   = implementation_detail;
    //    using query_modificator_param_type = implementation_detail;
    //    using query_parser_rule            = implementation_detail;

    //    using fragment_type                   = implementation_detail;
    //    using fragment_accessor_return_type   = implementation_detail;
    //    using fragment_modificator_param_type = implementation_detail;
    //    using fragment_parser_rule            = implementation_detail;
};



namespace helpers {

struct string_component_traits_base
{
    using type                   = std::string;
    using accessor_return_type   = type const &;
    using modificator_param_type = type const &;
};

template < template < typename > class ParserRuleT >
struct string_component_traits : string_component_traits_base
{
    template < typename Iterator >
    using parser_rule = ParserRuleT< Iterator >;
};

template < typename SchemeTraitsT,
           typename UserinfoTraitsT,
           typename HostTraitsT,
           typename PortTraitsT,
           typename PathTraitsT,
           typename QueryTraitsT,
           typename FragmentTraitsT >
struct composed_traits
{
    using scheme_type                   = typename SchemeTraitsT::type;
    using scheme_accessor_return_type   = typename SchemeTraitsT::accessor_return_type;
    using scheme_modificator_param_type = typename SchemeTraitsT::modificator_param_type;
    template < typename Iterator >
    using scheme_parser_rule = typename SchemeTraitsT::template parser_rule< Iterator >;

    using userinfo_type                   = typename UserinfoTraitsT::type;
    using userinfo_accessor_return_type   = typename UserinfoTraitsT::accessor_return_type;
    using userinfo_modificator_param_type = typename UserinfoTraitsT::modificator_param_type;
    template < typename Iterator >
    using userinfo_parser_rule = typename UserinfoTraitsT::template parser_rule< Iterator >;

    using host_type                   = typename HostTraitsT::type;
    using host_accessor_return_type   = typename HostTraitsT::accessor_return_type;
    using host_modificator_param_type = typename HostTraitsT::modificator_param_type;
    template < typename Iterator >
    using host_parser_rule = typename HostTraitsT::template parser_rule< Iterator >;

    using port_type                   = typename PortTraitsT::type;
    using port_accessor_return_type   = typename PortTraitsT::accessor_return_type;
    using port_modificator_param_type = typename PortTraitsT::modificator_param_type;
    template < typename Iterator >
    using port_parser_rule = typename PortTraitsT::template parser_rule< Iterator >;

    using path_type                   = typename PathTraitsT::type;
    using path_accessor_return_type   = typename PathTraitsT::accessor_return_type;
    using path_modificator_param_type = typename PathTraitsT::modificator_param_type;
    template < typename Iterator >
    using path_parser_rule = typename PathTraitsT::template parser_rule< Iterator >;

    using query_type                   = typename QueryTraitsT::type;
    using query_accessor_return_type   = typename QueryTraitsT::accessor_return_type;
    using query_modificator_param_type = typename QueryTraitsT::modificator_param_type;
    template < typename Iterator >
    using query_parser_rule = typename QueryTraitsT::template parser_rule< Iterator >;

    using fragment_type                   = typename FragmentTraitsT::type;
    using fragment_accessor_return_type   = typename FragmentTraitsT::accessor_return_type;
    using fragment_modificator_param_type = typename FragmentTraitsT::modificator_param_type;
    template < typename Iterator >
    using fragment_parser_rule = typename FragmentTraitsT::template parser_rule< Iterator >;
};

} // namespace helpers
} // namespace uri

#endif // uri__traits_hpp
