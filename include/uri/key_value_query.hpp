#ifndef uri__key_value_query_hpp
#define uri__key_value_query_hpp



#include <string>
#include <iterator>

#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/range/algorithm/transform.hpp>

#include <uri/percent/codec.hpp>



namespace uri
{
  template <class KeyValueQuery>
  std::string query_to_string( const KeyValueQuery & query )
  {
    std::vector<std::string> keyValueList;
    boost::transform( query, std::inserter( keyValueList, keyValueList.end() ),
                      []( const typename KeyValueQuery::value_type & queryItem )
                      { return percent::encode( queryItem.first ) + '=' + percent::encode( queryItem.second ); }
                    );

    return boost::algorithm::join( keyValueList, "&" );
  }


  template <class KeyValueQuery>
  KeyValueQuery string_to_query( const std::string & queryString )
  {
    if ( queryString.empty() ) { return KeyValueQuery{}; }

    std::vector<std::string> keyValueList;
    boost::algorithm::split( keyValueList, queryString, boost::algorithm::is_any_of( "&" ), boost::algorithm::token_compress_on );

    KeyValueQuery query;
    boost::transform( keyValueList,
                      std::inserter( query, query.end() ),
                      []( const std::vector<std::string>::value_type & keyValuePair )
                      {
                          std::vector<std::string> keyValue;
                          boost::algorithm::split( keyValue, keyValuePair, boost::algorithm::is_any_of( "=" ) );

                          auto it = keyValue.begin();

                          std::string key;
                          if ( it != keyValue.end() ) { key = percent::decode( *it ); ++it; }

                          std::string value;
                          if ( it != keyValue.end() ) { value = percent::decode( *it ); }

                          return std::make_pair( key, value );
                      }
                    );

    return query;
  }


} // namespace uri

#endif // ** uri__key_value_query_hpp ** //
