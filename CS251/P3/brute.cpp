#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "key.hpp"
#include "brute.hpp"
#include "timer.hpp"

std::string me;
std::string encrypted;
std::string table_filename;
bool verbose = false;

Brute::Brute(const std::string& filename) {
	T.resize(N);
	std::string buffer;
    std::fstream input(filename.c_str(), std::ios::in);
    for (int i = 0; i < N; i++) {
        std::getline(input, buffer);
        T[i].set_string(buffer);
    }
    input.close();
}

void Brute::permString(int position, std::string currPerm){
	Key ssum;

	for(int k = 0; k < 32; k++){
		currPerm[position] = ALPHABET[k];
		Key passkey((std::string(currPerm)));
		ssum = passkey.subset_sum(T, verbose);
		std::string checkEnc = ssum.returnEnc();
		if(checkEnc.compare(encrypted) == 0){
		  std::cout << currPerm << std::endl;
		}
		if(position > 0){
			permString(position - 1, currPerm);
		}
	}
}

void Brute::decrypt(const std::string& encrypted){

	std::string bruteStr = "";
	for(int i = 0; i < C;i++){
		bruteStr += 'a';
	}

	permString(C-1, bruteStr);
}

void usage(const std::string& error_msg="") {
	if (!error_msg.empty()) std::cout << "ERROR: " << error_msg << '\n';
	std::cout << me << ": Brute force cracking of Subset-sum password with "
		<< B << " bits precision\n"
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
  Brute *usageObj = new Brute(table_filename);
  usageObj -> decrypt(encrypted);
	// timer.toc();
	// std::cout << "Time: ";
	// std::cout << timer.elapsed() << '\n';
	return 0;
}
