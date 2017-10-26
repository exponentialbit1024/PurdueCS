#ifndef simplcommand_h
#define simplecommand_h
#include <vector>
#include <string>

struct SimpleCommand {
  // Available space for arguments currently preallocated
  int _numOfAvailableArguments;

  // Number of arguments
  int _numOfArguments;
  char ** _arguments;

  SimpleCommand();
  void insertArgument( char * argument );
  std::vector<int> findPositions(std::string, char target);
  std::vector<std::string> subexpansion(char * path);
};

#endif
