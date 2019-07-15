#ifndef uri__mailto_h
#define uri__mailto_h



#include <string>
#include <unordered_map>

#include <boost/utility/string_view.hpp>



///
/// RFC 6068 implementation
/// "https://tools.ietf.org/html/rfc6068"
///

namespace uri {

class mail_address
{
public:
    mail_address() = default;
    mail_address(const std::string & local_part_,
                 const std::string & domain_)
        : _local_part(local_part_),
          _domain(domain_)
    {}

    const std::string & local_part() const { return _local_part; }
    void local_part(const std::string & local_part_) { _local_part = local_part_; }

    const std::string & domain() const { return _domain; }
    void domain(const std::string & domain_) { _domain = domain_; }


private:
    std::string _local_part;
    std::string _domain;
};





class mailto
{
    using header_key = std::string;
    using header_value = std::string;
    using headers_type = std::unordered_map<header_key, header_value>;


public:
    mailto() = default;
    mailto(const std::string & scheme_,
           const mail_address & address_,
           const headers_type & headers_)
        : _scheme(scheme_)
        , _address(address_)
        , _headers(headers_)
    {}


    const std::string & scheme() const { return _scheme; }
    void scheme(const std::string & scheme_) { _scheme = scheme_; }

    const mail_address & address() const { return _address; }
    void address(const mail_address & address_) { _address = address_; }

    const headers_type & headers() const { return _headers; }
    void headers(const headers_type & headers_) { _headers = headers_; }

    const header_value & header(const header_key & key_) const { return _headers[key_]; }
    void header(const header_key & key_, const header_value & value_) { _headers[key_] = value_; }


    static mailto parse(const boost::string_view & str_);
    static std::string generate(const mailto & mailto_);


private:
    std::string  _scheme;
    mail_address _address;
    headers_type _headers;
};

mailto parse(const boost::string_view & str_)
{
    return mailto();
}

std::string generate(const mailto & mailtoUri_)
{
    return "";
}

} // namespace uri

#endif // uri__mailto_h
