/*
 * CS252: Shell project
 *
 * Template file.
 * You will need to add more code here to execute the command table.
 *
 * NOTE: You are responsible for fixing any bugs this code may have!
 *
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#include "command.hh"
#include <fcntl.h>


Command::Command()
{
	// Create available space for one simple command
	_numOfAvailableSimpleCommands = 1;
	_simpleCommands = (SimpleCommand **)
		malloc( _numOfSimpleCommands * sizeof( SimpleCommand * ) );

	_numOfSimpleCommands = 0;
	_outFile = 0;
	_inFile = 0;
	_errFile = 0;
	_background = 0;
	_append = 0;
	_errOutCnt = 0;
	_stdOutCnt = 0;
	_stdInCnt = 0;
}

void Command::insertSimpleCommand( SimpleCommand * simpleCommand ) {
	if ( _numOfAvailableSimpleCommands == _numOfSimpleCommands ) {
		_numOfAvailableSimpleCommands *= 2;
		_simpleCommands = (SimpleCommand **) realloc( _simpleCommands,
			 _numOfAvailableSimpleCommands * sizeof( SimpleCommand * ) );
	}
	
	_simpleCommands[ _numOfSimpleCommands ] = simpleCommand;
	_numOfSimpleCommands++;
}

void Command:: clear() {
	for ( int i = 0; i < _numOfSimpleCommands; i++ ) {
		for ( int j = 0; j < _simpleCommands[ i ]->_numOfArguments; j ++ ) {
			free ( _simpleCommands[ i ]->_arguments[ j ] );
		}
		
		free ( _simpleCommands[ i ]->_arguments );
		free ( _simpleCommands[ i ] );
	}

	if ( _outFile && _errFile) {
		free( _outFile );
	}else if(_outFile){
		free( _outFile);
	}else if( _errFile){
		free(_errFile);
	}

	if ( _inFile ) {
		free( _inFile );
	}

	_numOfSimpleCommands = 0;
	_outFile = 0;
	_inFile = 0;
	_errFile = 0;
	_background = 0;
	_append = 0;
	_errOutCnt = 0;
	_stdOutCnt = 0;
	_stdInCnt = 0;
}

void Command::print() {
	printf("\n\n");
	printf("              COMMAND TABLE                \n");
	printf("\n");
	printf("  #   Simple Commands\n");
	printf("  --- ----------------------------------------------------------\n");
	
	for ( int i = 0; i < _numOfSimpleCommands; i++ ) {
		printf("  %-3d ", i );
		for ( int j = 0; j < _simpleCommands[i]->_numOfArguments; j++ ) {
			printf("\"%s\" \t", _simpleCommands[i]->_arguments[ j ] );
		}
	}

	printf( "\n\n" );
	printf( "  Output       Input        Error        Background\n" );
	printf( "  ------------ ------------ ------------ ------------\n" );
	printf( "  %-12s %-12s %-12s %-12s\n", _outFile?_outFile:"default",
		_inFile?_inFile:"default", _errFile?_errFile:"default",
		_background?"YES":"NO");
	printf( "\n\n" );
	
}

void Command::execute() {
	// Don't do anything if there are no simple commands
	if ( _numOfSimpleCommands == 0 ) {
		prompt();
		return;
	}

	// Print contents of Command data structure
	//print();

	// Add execution here
	// For every simple command fork a new process
	if(_errOutCnt > 1 || _stdOutCnt > 1 || _stdInCnt > 1){
		printf("Ambiguous output redirect\n");
		clear();
		prompt();
		return;
	}
	int ret;
	int fdout;
	int fdin;
	int fderr;
	int tempin = dup(0);
	int tempout = dup(1);
	int temperr = dup(2);
	if(_inFile){
		fdin = open(_inFile, O_RDONLY, 0664);
		if(fdin < 0){
			perror("open");
			_exit(1);
		}
	}else{
			fdin = dup(tempin);
	}
	if(_errFile){
		fderr = open(_errFile, O_WRONLY|O_CREAT|O_APPEND, 0664);
		if(fderr < 0){
			perror("open");
			_exit(1);
		}
	}else{
		fderr = dup(temperr);
	}
	for(int i = 0; i < _numOfSimpleCommands; i++){
		dup2(fdin, 0);
		dup2(fderr, 2);
		close(fdin);
		if(i == _numOfSimpleCommands - 1){
				if(_outFile){
					if(_append){
						fdout = open(_outFile, O_WRONLY|O_CREAT|O_APPEND, 0664);
					}else{
						fdout = open(_outFile,O_WRONLY|O_CREAT|O_TRUNC, 0664);
					}
					if(fdout < 0){
						perror("open");
						_exit(1);
					}
				}else if(_errFile){
					if(_append){
						fdout = open(_errFile, O_WRONLY|O_CREAT|O_APPEND, 0664);
					}else{
						fdout = open(_errFile, O_WRONLY|O_CREAT|O_TRUNC, 0664);
					}
					if(fdout < 0){
						perror("open");
						_exit(1);
					}
				}else{
					fdout = dup(tempout);
				}
		}else{
			int fdpipe[2];
			pipe(fdpipe);
			fdout = fdpipe[1];
			fdin = fdpipe[0];
		}
		dup2(fdout, 1);
		close(fdout);
		ret = fork();
		if(ret == 0){
			//child
			execvp(_simpleCommands[i] -> _arguments[0], _simpleCommands[i] -> _arguments);
			perror("execvp");
			_exit(1);
		}else if(ret < 0){
			perror("fork");
			_exit(2);
		}
	}
	dup2(tempin, 0);
	dup2(tempout, 1);
	dup2(temperr, 2);
	close(tempin);
	close(tempout);
	close(temperr);
	if(!_background){
		waitpid(ret, NULL, 0);
	}
	// Setup i/o redirection
	// and call exec

	// Clear to prepare for next command
	clear();
	
	// Print new prompt
	prompt();
}

// Shell implementation

void Command::prompt() {
	if(isatty(0)){
		printf("myshell>");
		fflush(stdout);
	}
}

Command Command::_currentCommand;
SimpleCommand * Command::_currentSimpleCommand;
