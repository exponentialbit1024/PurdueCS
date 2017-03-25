#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

#include "key.hpp"
#include "symbol.hpp"
#include "timer.hpp"

std::string me;
std::string encrypted;
std::string table_filename;
bool verbose = false;
Key encryptedKey;

Symbol::Symbol(const std::string& filename) {
	T.resize(N);
	std::string buffer;
    std::fstream input(filename.c_str(), std::ios::in);
    for (int i = 0; i < N; i++) {
        std::getline(input, buffer);
        T[i].set_string(buffer);
    }
    input.close();
		encryptedKey = Key((std::string(encrypted)));
}

void Symbol::perm2String(int position, std::string currPerm){
	Key ssum;

	for(int k = 0; k < 32; k++){
		currPerm[position + (C/2)] = ALPHABET[k];
		Key passkey((std::string(currPerm)));
		ssum = passkey.subset_sum(T, verbose);
		std::string checkEnc = ssum.returnEnc();

	  S.insert(make_pair(checkEnc,currPerm));

		if(position > 0){
			perm2String(position - 1, currPerm);
		}
	}

}

void Symbol::perm1String(int position, std::string currPerm){
	Key ssum;

	for(int k = 0; k < 32; k++){
		currPerm[position] = ALPHABET[k];
		Key passkey((std::string(currPerm)));
		ssum = passkey.subset_sum(T, verbose);

		Key subtraction = ssum.subtractor(encryptedKey, ssum);

		// ssum.show();
		auto search = S.find(subtraction.returnEnc());
		if(search != S.end()){
			if(C % 2 == 0){
					std::cout << currPerm.substr(0, C/2);
			}else{
				std::cout << currPerm.substr(0, C/2 + 1);
			}

			std::cout << S[subtraction.returnEnc()].substr(C/2,C) << '\n';
		}
		if(position > 0){
			perm1String(position - 1, currPerm);
		}
	}

}

void Symbol::decrypt(const std::string& encrypted){
	std::string bruteStr = "";
	for(int i = 0; i < C;i++){
		bruteStr += 'a';
	}
	if(C % 2 == 0){
			perm2String ((C / 2) - 1, bruteStr);
	}else{
		perm2String((C / 2), bruteStr);
	}

	perm1String((C / 2) - 1, bruteStr);
}

void usage(const std::string& error_msg="") {
	if (!error_msg.empty()) std::cout << "ERROR: " << error_msg << '\n';
	std::cout << me << ": Symbol table-based cracking of Subset-sum password"
		<< " with " << B << " bits precision\n"
	    << "USAGE: " << me << " <encrypted> <table file> [options]\n"
		<< "\nArguments:\n"
		<< " <encrypted>:   encrypted password to crack\n"
		<< " <table file>:  name of file containing the table to use\n"
		<< "\nOptions:\n"
		<< " -h|--help:     print this message\n"
		<< " -v|--verbose:  select verbose mode\n\n";
	exit(0);
}

void initialize(int argc, char* argv[]) {
	me = argv[0];
	if (argc < 3) usage("Missing arguments");
	encrypted = argv[1];
	table_filename = argv[2];
	for (int i=3; i<argc; ++i) {
		std::string arg = argv[i];
		if (arg == "-h" || arg == "--help") usage();
		else if (arg == "-v" || arg == "--verbose") verbose = true;
		else usage("Unrecognized argument: " + arg);
	}
}


int main(int argc, char *argv[]){
	CPU_timer timer;
	timer.tic();
	initialize(argc, argv);

	Symbol *usageObj = new Symbol(table_filename);
  usageObj -> decrypt(encrypted);
	timer.toc();
	std::cout << "Time : ";
	std::cout << timer.elapsed() << '\n';
	return 0;
}
