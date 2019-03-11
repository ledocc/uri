#ifndef uri__uri_hpp
#define uri__uri_hpp



#include <uri/basic_uri.hpp>
#include <uri/parsers/rules/uri/fragment.hpp>
#include <uri/parsers/rules/uri/host.hpp>
#include <uri/parsers/rules/uri/path.hpp>
#include <uri/parsers/rules/uri/port.hpp>
#include <uri/parsers/rules/uri/query.hpp>
#include <uri/parsers/rules/uri/scheme.hpp>
#include <uri/parsers/rules/uri/userinfo.hpp>
#include <uri/traits.hpp>

#include <string>



namespace uri {

struct uri_tag
{};



using string_scheme_trait   = helpers::string_component_traits< parsers::rules::uri::scheme >;
using string_userinfo_trait = helpers::string_component_traits< parsers::rules::uri::userinfo >;
using string_host_trait     = helpers::string_component_traits< parsers::rules::uri::host >;
using string_port_trait     = helpers::string_component_traits< parsers::rules::uri::port >;
using string_path_trait     = helpers::string_component_traits< parsers::rules::uri::path >;
using string_query_trait    = helpers::string_component_traits< parsers::rules::uri::query >;
using string_fragment_trait = helpers::string_component_traits< parsers::rules::uri::fragment >;

template <>
struct traits< uri_tag > : public helpers::composed_traits< string_scheme_trait,
                                                            string_userinfo_trait,
                                                            string_host_trait,
                                                            string_port_trait,
                                                            string_path_trait,
                                                            string_query_trait,
                                                            string_fragment_trait >
{};

using uri = basic_uri< uri_tag >;

} // namespace uri

#endif // uri__uri_hpp
