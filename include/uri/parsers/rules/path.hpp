#ifndef uri__parsers__rules__path_hpp
#define uri__parsers__rules__path_hpp

#define BOOST_SPIRIT_DEBUG

#include <string>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/fusion/include/std_tuple.hpp>

#include <uri/parsers/rules/character.hpp>



namespace phoenix = boost::phoenix;
namespace fusion = boost::fusion;
namespace spirit = boost::spirit;
namespace ascii = boost::spirit::ascii;
namespace qi = boost::spirit::qi;

namespace uri { namespace parsers { namespace rules {


template <typename Iterator>
class path
{public:
    using rule_string = qi::rule<Iterator, std::string()>;

    path()
    {
        _path            = _path_abempty
                         | _path_absolute
                         | _path_noscheme
                         | _path_rootless
                         | _path_empty;

        // path-abempty  = *( "/"     segment )
        _path_abempty    = *( ascii::char_('/') > _segment );
        // path-absolute = "/"    [   segment-nz    *( "/"     segment ) ]
        _path_absolute   = ascii::char_('/') > -( _segment_nz >> *( ascii::char_('/') >> _segment ) );
        // path-noscheme =  segment-nz-nc    *( "/"     segment )
        _path_noscheme   = _segment_nz_nc > *( ascii::char_('/')>> _segment );
        // path-rootless =  segment-nz    *( "/"     segment )
        _path_rootless   = _segment_nz > *( ascii::char_('/') > _segment );
        // path-empty    = 0<pchar>
        _path_empty      = !_char.pchar();

        // segment       = * pchar
        _segment         = *_char.pchar();
        // segment-nz    = 1*pchar
        _segment_nz      = +_char.pchar();
        // segment-nz-nc = 1*( unreserved /  pct-encoded  / sub-delims /  "@" )
        //                 ; non-zero-length segment without any colon ":"
        _segment_nz_nc   = +( _char.unreserved() | _char.percent_encoded() | _char.sub_delims() | ascii::char_('@') );

    }

    void enable_debug()
    {
        BOOST_SPIRIT_DEBUG_NODE(_path);
        BOOST_SPIRIT_DEBUG_NODE(_path_abempty);
        BOOST_SPIRIT_DEBUG_NODE(_path_noscheme);
        BOOST_SPIRIT_DEBUG_NODE(_path_rootless);
        BOOST_SPIRIT_DEBUG_NODE(_path_absolute);
        BOOST_SPIRIT_DEBUG_NODE(_path_empty);
    }

    const rule_string & operator()() const { return _path; }
    const rule_string & abempty() const    { return _path_abempty; }
    const rule_string & noscheme() const   { return _path_noscheme; }
    const rule_string & rootless() const   { return _path_rootless; }
    const rule_string & absolute() const   { return _path_absolute; }
    const rule_string & empty() const      { return _path_empty; }


private:
    rule_string _path;
    rule_string _path_abempty;
    rule_string _path_absolute;
    rule_string _path_noscheme;
    rule_string _path_rootless;
    rule_string _path_empty;
    rule_string _segment;
    rule_string _segment_nz;
    rule_string _segment_nz_nc;
    rules::character<Iterator> _char;
};

}}} // namespace uri::parsers::rules

#endif // uri__parsers__rules__path_hpp
