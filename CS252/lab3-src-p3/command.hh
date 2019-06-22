#ifndef command_h
#define command_h

#include "simpleCommand.hh"

// Command Data Structure

struct Command {
  int _numOfAvailableSimpleCommands;
  int _numOfSimpleCommands;
  SimpleCommand ** _simpleCommands;
  char * _outFile;
  char * _inFile;
  char * _errFile;
//  char * currPath;
  int _background;
  int _append;
  int _errOutCnt;
  int _stdOutCnt;
  int _stdInCnt;

  void prompt();
  void print();
  void execute();
  void clear();

  Command();
  void insertSimpleCommand( SimpleCommand * simpleCommand );
//  void setCurrentShellPath(char * path);
  int isBuiltIn(int index);
  static Command _currentCommand;
  static SimpleCommand *_currentSimpleCommand;
};

#endif
