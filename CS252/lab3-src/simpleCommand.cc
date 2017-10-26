#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simpleCommand.hh"
#include <string>
#include <sys/types.h>
#include <dirent.h>
#include <algorithm>
#include <iostream>
#include <sys/types.h>
#include <regex.h>
#include <unistd.h>

SimpleCommand::SimpleCommand() {
	// Create available space for 5 arguments
	_numOfAvailableArguments = 5;
	_numOfArguments = 0;
	_arguments = (char **) malloc( _numOfAvailableArguments * sizeof( char * ) );
}

void SimpleCommand::insertArgument( char * argument ) {
	if ( _numOfAvailableArguments == _numOfArguments  + 1 ) {
		// Double the available space
		_numOfAvailableArguments *= 2;
		_arguments = (char **) realloc( _arguments,
				  _numOfAvailableArguments * sizeof( char * ) );
	}
	
	std::string argstr(argument);
	int find = argstr.find('~');
	if(find != -1){
		if(argstr.length() == 1){
			argument = getenv("HOME");
		}else{
			int findbs = argstr.find("/");
			char homedir[] = "/homes/";
			std::string newHomestr(homedir);
			if(findbs == -1){
				newHomestr.append(argstr.substr(find + 1, argstr.size()));
				argument = (char *)newHomestr.c_str();
			}else{
				argstr.erase(find, 1);
				argstr.insert(0, homedir, 7);
				argument = (char *)argstr.c_str();
			}
		}
	}
	
	int findwcs = argstr.find("*");
	if(findwcs != -1){
		if(argstr.length() == 1){
			DIR *currDir = opendir(get_current_dir_name());
			struct dirent *pDirent;
			std::vector<std::string> sortedFiles;
			while ((pDirent = readdir(currDir)) != NULL) {
				if(strcmp(pDirent -> d_name, ".") != 0 && strcmp(pDirent -> d_name, "..") && (pDirent -> d_name[0] != '.')){
					std::string fname = pDirent -> d_name;
					sortedFiles.push_back(fname);
				}
			}
			std::sort(sortedFiles.begin(), sortedFiles.end());
			std::string finArg;
			for(std::vector<int>::size_type i = 0; i != sortedFiles.size(); i++) {
				finArg.append(sortedFiles[i]);
				if(i + 1 != sortedFiles.size()){
					finArg.append(" ");
				}
			}
			//strcpy(argument, (char *) finArg.c_str());
			argument = strdup((char *) finArg.c_str());
		}else{
			int findwcbs = argstr.find_last_of("/");
			if(findwcbs != -1){
				char *newDir = (char *)malloc(sizeof(char) * findwcbs);
				int h;
				for(h = 0; h < findwcbs; h++){
					newDir[h] = argument[h];
				}
				newDir[h] = '/';
				h++;
				newDir[h] = '\0';
					
				std::string remrexl = argstr.substr(h, argstr.length());
				if(remrexl.length() == 1){
					remrexl.insert(0, ".", 1);
				}else{
					remrexl.insert(0, "^", 1);
					std::vector<int> allPos = findPositions(remrexl, '*');
					int cins = 0;
					for(std::vector<int>::size_type aa = 0; aa != allPos.size(); aa++){
						//std::cout << allPos[aa] << "\n\n";
						remrexl.insert(allPos[aa] + cins, ".");
						cins++;
					}
				}
				//remrexl += '$';
				//std::cout << remrexl << "\n\n";
				regex_t re;
				int result = regcomp(&re, remrexl.c_str(), REG_EXTENDED|REG_NOSUB);
				if(result != 0){
					printf("error pattern");
					exit(-1);
				}
				regmatch_t match;

				DIR *currDir = opendir(newDir);
				struct dirent *pDirent;
				std::vector<std::string> sortedFiles;
				while ((pDirent = readdir(currDir)) != NULL) {
					if(strcmp(pDirent -> d_name, ".") != 0 && strcmp(pDirent -> d_name, "..")){
						result = regexec(&re, pDirent -> d_name, 1, &match, 0);
						if(result == 0){
							std::string fname = pDirent -> d_name;
							sortedFiles.push_back(fname);
						}
					}
				}
				std::sort(sortedFiles.begin(), sortedFiles.end());
				std::string finArg;
				std::string newDirstr(newDir);
				for(std::vector<int>::size_type i = 0; i != sortedFiles.size(); i++) {
					finArg.append(newDirstr);
					finArg.append(sortedFiles[i]);
					if(i + 1 != sortedFiles.size()){
						finArg.append(" ");
					}
				}
				//strcpy(argument, (char *) finArg.c_str());
				argument = strdup((char *) finArg.c_str());
			}else{
				regex_t re;
				int result = regcomp(&re, argstr.c_str(), REG_EXTENDED|REG_NOSUB);
				if(result != 0){
					printf("error pattern");
					exit(-1);
				}
				regmatch_t match;
				DIR *currDir = opendir(get_current_dir_name());
				struct dirent *pDirent;
				std::vector<std::string> sortedFiles;
				while ((pDirent = readdir(currDir)) != NULL) {
					if(!(pDirent -> d_name[0] != '.')){
						result = regexec(&re, pDirent -> d_name, 1, &match, 0);
						if(result == 0){
							std::string fname = pDirent -> d_name;
							sortedFiles.push_back(fname);
						}
					}
				}
				std::sort(sortedFiles.begin(), sortedFiles.end());
				std::string finArg;
				for(std::vector<int>::size_type i = 0; i != sortedFiles.size(); i++) {
					finArg.append(sortedFiles[i]);
					if(i + 1 != sortedFiles.size()){
						finArg.append(" ");
					}
				}
				//strcpy(argument, (char *) finArg.c_str());
				argument = strdup((char *) finArg.c_str());
			}
		}
	}

	_arguments[ _numOfArguments ] = argument;

	// Add NULL argument at the end
	_arguments[ _numOfArguments + 1] = NULL;
	
	_numOfArguments++;
}

std::vector<int> SimpleCommand::findPositions(std::string regstr, char tgt){
	std::vector<int> characterLocations;
	for(unsigned int i =0; i < regstr.size(); i++){
		if(regstr[i] == tgt){
			characterLocations.push_back(i);
		}
	}
	return characterLocations;
}

std::vector<std::string> SimpleCommand::subexpansion(char * brokenpath){
	std::string bpstr = brokenpath;
	std::vector<int> allStpos = findPositions(bpstr, '*');
		
}

