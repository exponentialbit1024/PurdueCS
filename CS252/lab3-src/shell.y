
/*
 * CS-252
 * shell.y: parser for shell
 *
 * This parser compiles the following grammar:
 *
 *	cmd [arg]* [> filename]
 *
 * you must extend it to understand the complete shell grammar
 *
 */

%code requires 
{
#include <string>

#if __cplusplus > 199711L
#define register      // Deprecated in C++11 so remove the keyword
#endif
}

%union
{
  char        *string_val;
  // Example of using a c++ type in yacc
  std::string *cpp_string;
}

%token <string_val> WORD QUOTE
%token NOTOKEN GREAT NEWLINE GREATGREAT PIPE AMPERSAND LESS GREATAMPERSAND GREATGREATAMPERSAND TWOGREAT

%{
//#define yylex yylex
#include <cstdio>
#include "command.hh"
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void yyerror(const char * s);
int yylex();

%}

%%

goal:
  commands
  ;

commands:
  command
  | commands command
  ;

command: simple_command
       ;

simple_command:	
  pipe_list io_modifier_list background_opt NEWLINE {
/*    printf("   Yacc: Execute command\n"); */
    Command::_currentCommand.execute();
  }
  | NEWLINE 
  | error NEWLINE { yyerrok; }
  ;

pipe_list:
  pipe_list PIPE command_and_args
  | command_and_args
  ;
 
command_and_args:
  command_word argument_list {
    Command::_currentCommand.
    insertSimpleCommand( Command::_currentSimpleCommand );
  }
  ;

argument_list:
  argument_list argument
  | /* can be empty */
  ;

argument:
  QUOTE {
	/*printf("quote %s", remQ);*/
  	Command::_currentSimpleCommand -> insertArgument($1);
  }
  | WORD {
    /*printf("   Yacc: insert argument %s\n", remE);*/
    Command::_currentSimpleCommand->insertArgument( $1 );
  }
  ;

command_word:
  WORD {
    /*printf("   Yacc: insert command %s\n", $1);*/
    Command::_currentSimpleCommand = new SimpleCommand();
    Command::_currentSimpleCommand->insertArgument( $1 );
  }
  ;

iomodifier_opt:
  TWOGREAT WORD {
  	/*printf("   Yacc: insert redirect error \"%s\"\n", $2);*/
	Command::_currentCommand._errFile = $2;
	Command::_currentCommand._errOutCnt++;
  }
  | GREATGREATAMPERSAND WORD {
  	/*printf("   Yacc: insert append redirect both \"%s\"\n", $2); */
/*	Command::_currentCommand._outFile = $2;*/
	Command::_currentCommand._errFile = $2;
  	Command::_currentCommand._append = 1;
  	Command::_currentCommand._errOutCnt++;
  } 
  | GREATGREAT WORD {
  	/*printf("   Yacc: insert output \"%s\"\n", $2);*/
	Command::_currentCommand._outFile = $2;
  	Command::_currentCommand._append = 1;
  	Command::_currentCommand._stdOutCnt++;
  }
  | GREATAMPERSAND WORD {
  	/*printf("   Yacc: insert redirect output \"%s\"\n", $2);*/
	/*Command::_currentCommand._outFile = $2;*/
	Command::_currentCommand._errFile = $2;
	Command::_currentCommand._errOutCnt++;
  }
  | GREAT WORD {
    /*printf("   Yacc: insert output \"%s\"\n", $2);*/
    Command::_currentCommand._outFile = $2;
  	Command::_currentCommand._stdOutCnt++;
  }
  | LESS WORD {
  	/*printf("   Yacc: insert input \"%s\"\n", $2);*/
	Command::_currentCommand._inFile = $2;
  	Command::_currentCommand._stdInCnt++;
  } 
  ;

io_modifier_list:
  io_modifier_list iomodifier_opt
  | /* can be empty */
  ;

background_opt:
  AMPERSAND {
  	Command::_currentCommand._background = 1;
  }
  | /* can be empty */
  ;

%%

void
yyerror(const char * s)
{
  fprintf(stderr,"%s", s);
}

#if 0
main()
{
  yyparse();
}
#endif
