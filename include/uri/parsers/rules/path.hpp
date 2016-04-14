#ifndef uri__parsers__rules__path_hpp
#define uri__parsers__rules__path_hpp



#include <string>

#include <boost/spirit/include/qi.hpp>

#include <uri/parsers/rules/character.hpp>



namespace uri { namespace parsers { namespace rules {

template <typename Iterator>
class path
{
public:
    using rule_type = boost::spirit::qi::rule<Iterator, std::string()>;


    path()
    {
        namespace ascii = boost::spirit::ascii;


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

    const rule_type & operator()() const { return _path; }
    const rule_type & abempty() const    { return _path_abempty; }
    const rule_type & noscheme() const   { return _path_noscheme; }
    const rule_type & rootless() const   { return _path_rootless; }
    const rule_type & absolute() const   { return _path_absolute; }
    const rule_type & empty() const      { return _path_empty; }


private:
    rule_type _path;
    rule_type _path_abempty;
    rule_type _path_absolute;
    rule_type _path_noscheme;
    rule_type _path_rootless;
    rule_type _path_empty;
    rule_type _segment;
    rule_type _segment_nz;
    rule_type _segment_nz_nc;
    rules::character<Iterator> _char;
};

}}} // namespace uri::parsers::rules

#endif // uri__parsers__rules__path_hpp
