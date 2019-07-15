

#include <uri/uri.hpp>


int main()
{
  uri::uri uri;
  uri.scheme( "https" );
  uri.host( "github.com" );
  uri.path( "/ledocc/uri.git" );

  return 0;
}
