
/*
 *
 * CS-252 Fall 2017
 * shell.l: lexical analyzer for shell
 * You have to extend it.
 *
 */

%{

#include <cstring>
#include <string.h>
#include "y.tab.hh"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static  void yyunput (int c,char *buf_ptr  );

extern "C" char * read_line();

int mygetc(FILE* f) {
  static char *p;
  char ch;
  if(!isatty(0)){
  	return getc(f);
  }
  if(p == NULL || *p == 0){
  	char *s = read_line();
	p = s;
  }
  ch = *p;
  p++;
  return ch;
}

#undef getc
#define getc(f) mygetc(f)

void myunputc(int c) {
  unput(c);
}

%}

%%

\n {
  return NEWLINE;
}

[ \t] {
  /* Discard spaces and tabs */
}

"2>" {
  return TWOGREAT;
}

">>&" {
  return GREATGREATAMPERSAND;
}

">>" {
  return GREATGREAT;
}

">&" {
  return GREATAMPERSAND;
}

">" {
  return GREAT;
}

"<" {
  return LESS;
}

"|" {
  return PIPE;
}

"&" {
  return AMPERSAND;
}

`[^\n`]*` {
	char *command = strdup(yytext);
	char *remQ = (char *)malloc(strlen(command) - 2);
	int k = 0;
	for(int i = 1; i < strlen(command) - 1; i++){
		remQ[k] = command[i];
		k++;
	}
	remQ[k] = '\0';
	int tempin = dup(0);
	int tempout = dup(1);
	
	int fdpipein[2];
	int fdpipeout[2];

	pipe(fdpipein);
	pipe(fdpipeout);

	write(fdpipein[1], remQ, strlen(remQ));
	write(fdpipein[1], "\n", 1);
	write(fdpipein[1], "exit", 4);
	write(fdpipein[1], "\n", 1);

	close(fdpipein[1]);

	int ret = fork();
	dup2(fdpipein[0], 0);
	close(fdpipein[0]);
	dup2(fdpipeout[1], 1);
	close(fdpipeout[1]);

	if(ret == 0){
		dup2(1, fdpipeout[1]);
		execvp("/proc/self/exe", NULL);
		_exit(1);
	}else if(ret < 0){
		perror("fork");
		exit(1);
	}

	dup2(tempin, 0);
	dup2(tempout, 1);
	close(tempin);
	close(tempout);

	char ch;
	char *buffer = (char *)malloc(1024);
	int o = 0;
	while(read(fdpipeout[0], &ch, 1)){
		if(ch == '\n'){
			buffer[o++] = ' ';
		}else{
			buffer[o++] = ch;
		}
	}
	buffer[o] = '\0';
	for(o = strlen(buffer); o >= 0; o--){
		unput(buffer[o]);
	}
}

["][^\n\"]*["] {
	yytext[strlen(yytext+1)] = '\0';
	yylval.string_val = strdup(yytext+1);
	return QUOTE;
}

[^ \t\n|<>&]*\\[^ \t\n]* {
	int i = 0;
	char *remE = (char *) malloc (strlen(yytext) - 1);
	for(int j = 0; j < strlen(yytext); j++){
		if(yytext[j] == '\\'){
			if((j + 1) < strlen(yytext) && yytext[j + 1] == '\\'){
				remE[i++] = '\\';
				j += 2;
			}else{
				remE[i++] = yytext[j + 1];
				j++;
			}
		}else{
			remE[i] = yytext[j];
			i++;
		}
	}
	remE[i] = '\0';
	yylval.string_val = strdup(remE);
	return WORD;
}

[^ \t\n|<>][^ \t\n|<>]* {
	yylval.string_val = strdup(yytext);
	return WORD;
}
