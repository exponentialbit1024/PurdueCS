
#include <stdio.h>

#define LF 10

extern "C" void
httprun(int ssock, char * query_string)
{
  FILE * fssock = fdopen( ssock, "r+");

  if ( fssock == NULL ) {
    perror("fdopen");
  }
	
  fprintf( fssock, "HTTP/1.1 200 Document follows%c",LF);
  fprintf( fssock, "Server: CS 252 lab5%c", LF);
  fprintf( fssock, "Content-type: text/html%c%c",LF,LF);
  
  
  fprintf( fssock, "<h1>Hello. Hi from hello.so</h1>\n");

  fclose( fssock );
}

