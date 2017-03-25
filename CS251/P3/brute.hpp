#ifndef _BRUTE_HPP_
#define _BRUTE_HPP_

#include <fstream>
#include <iostream>
#include <string>

#include "key.hpp"

class Brute {
private:
	std::vector<Key> T;

public:
	Brute(const std::string&);
	void decrypt(const std::string&);
	void permString(int, std::string);
};

#endif
