/**********************************************************************
 *  Encrypt a file using subset-sum algorithm.
 *
 *  Execution:      % ./encrypt password < rand8.txt
 *                  vbskbezp
 *
 *  Note: need to set C = 8 in key.h before compiling and executing
 *        with rand8.txt.
 *
 **********************************************************************/

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "key.hpp"

std::string me;
std::string password;
std::string table_filename;
bool verbose = false;

void usage(const std::string& error_msg="") {
	if (!error_msg.empty()) std::cout << "ERROR: " << error_msg << '\n';
	std::cout << me << ": Subset-sum password encryption with "
		<< B << " bits precision\n"
	    << "USAGE: " << me << " <password> <table file> [options]\n"
		<< "\nArguments:\n"
		<< " <password>:    password to encrypt\n"
		<< " <table file>:  name of file containing the table to use\n"
		<< "\nOptions:\n"
		<< " -h|--help:     print this message\n"
		<< " -v|--verbose:  select verbose mode\n\n";
	exit(0);
}

void initialize(int argc, char* argv[]) {
	me = argv[0];
	if (argc < 3) usage("Missing arguments");
	password = argv[1];
	table_filename = argv[2];
	for (int i=3; i<argc; ++i) {
		std::string arg = argv[i];
		if (arg == "-h" || arg == "--help") usage();
		else if (arg == "-v" || arg == "--verbose") verbose = true;
		else usage("Unrecognized argument: " + arg);
	}
}


int main(int argc, char *argv[]) {
    int i;
    std::string buffer;
    std::vector<Key> T(N); // the table T
    Key ssum;

    initialize(argc, argv);

    // Create a Key from the input password
    Key passkey((std::string(argv[1])));

    // Print out input password
    if (verbose) {
		std::cout << "   ";
    	passkey.show();
    	std::cout << std::endl;
	}

    // Read in table T
    std::fstream input(argv[2], std::ios::in);
    for (i = 0; i < N; i++) {
        std::getline(input, buffer);
        T[i].set_string(buffer);
    }
    input.close();

    // Compute subset sum
    ssum = passkey.subset_sum(T, verbose);

    // Print results
    if (verbose) std::cout << std::endl << "   ";
    ssum.show();

    return 0;
}
