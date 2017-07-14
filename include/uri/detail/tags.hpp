#ifndef uri__detail__tags_hpp
#define uri__detail__tags_hpp

namespace uri { namespace detail {

struct scheme_tag {};
struct host_tag {};
struct port_tag {};
struct userinfo_tag {};
struct path_tag {};
struct query_tag {};
struct fragment_tag {};

}} // namespace uri::detail

#endif // uri__detail__tags_hpp
