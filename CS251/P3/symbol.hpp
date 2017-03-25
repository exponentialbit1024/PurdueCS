#ifndef _SYMBOL_HPP_
#define _SYMBOL_HPP_

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "key.hpp"

class Symbol {
private:
	std::vector<Key> T;
	std::unordered_map<std::string, std::string> S;
public:
	Symbol(const std::string&);
	void decrypt(const std::string&);
	void perm1String(int, std::string);
	void perm2String(int, std::string);
};

#endif
