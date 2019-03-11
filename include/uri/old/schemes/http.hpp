#ifndef http__key_value_query_h
#define http__key_value_query_h



#include <string>
#include <unordered_map>

#include <boost/range.hpp>

namespace http {

template <typename AssociativeContainerT >
std::string generate(const AssociativeContainerT & src,
                     const char keyValueDelimiter = '=',
                     const char elementDelimiter = '&')
{
    if (src.empty()) { return std::string(); }

    auto range = boost::make_iterator_range(src);

    const auto & element = range.front();
    std::string result = encode(element.first()) + keyValueDelimiter + encode(element.first());
    range = range.advance_begin(1);

    for (const auto & element : range)
    {
        result += elementDelimiter
                + encode(element.first())
                + keyValueDelimiter
                + encode(element.second());
    }

    return result;
}

} // namespace http

#endif // http__key_value_query_h
