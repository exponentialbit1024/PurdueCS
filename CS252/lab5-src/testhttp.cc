#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int QueueLength = 15;

const char *secret = "5J1vCTsHxe9X79PyLDjQhZAtCYJPK8us0A9xnjjQ";

void serveFile(int fd, char * currPath){
	std::string secretStr(secret);
	const int MaxName = 1024;
	char name[MaxName + 1];
	int nameLength = 0;
	int n;

	unsigned char newChar;
	unsigned char lastChar = 0;
	while(nameLength < MaxName && (n = read(fd, &newChar, sizeof(newChar) )) > 0){
		if(lastChar == '\015' && newChar == '\012'){
			nameLength--;
			break;
		}
		name[nameLength] = newChar;
		nameLength++;
		lastChar = newChar;
	}
	name[nameLength] = 0;
	std::string requestStr(name);
	int pathindex = requestStr.find("/");
	std::string pathStr = requestStr.substr(pathindex + 1, pathindex + 36);
	int secretCompare = pathStr.compare(secretStr);
	if(!secretCompare){
		char * rpath = (char *)malloc(1024);
		realpath(currPath, rpath);
		std::string rpathstr(rpath);
		free(rpath);
		int lastsl = rpathstr.find_last_of('/');
		std::string rdirpath = rpathstr.substr(0, lastsl + 1);
		if(requestStr.at(pathindex + 41) == ' '){
			rdirpath.append("http-root-dir/htdocs/index.html");
			string fileLine;
			string allLines;
			ifstream indexF(rdirpath.c_str());
			if(indexF.is_open()){
				while(getline(indexF, fileLine)){
					allLines.append(fileLine + "\n");
				}
				indexF.close();
			}else{
				printf("Not Found");
			}
			std::string responseStr("HTTP/1.1 200 \nServer: CS 252 lab5\nContent-type: text/html\n\n");
			responseStr.append(allLines);
			cout << responseStr << "\n";
			write(fd, responseStr.c_str(), strlen(responseStr.c_str()));
		}else{
			printf("Not Found");
		}
	}else{
		printf("some error");
		exit(-1);
	}
}

int main(int argc, char ** argv){
	// Add your HTTP implementation here
	int port = atoi(argv[argc - 1]);
	struct sockaddr_in serverIPAddress;
	memset(&serverIPAddress, 0, sizeof(serverIPAddress));
	serverIPAddress.sin_family = AF_INET;
	serverIPAddress.sin_addr.s_addr = INADDR_ANY;
	serverIPAddress.sin_port = htons((u_short) port);
	
	int masterSocket = socket(PF_INET, SOCK_STREAM, 0);
	if(masterSocket < 0){
		perror("socket");
		exit(-1);
	}
	int optval = 1;
	int err = setsockopt(masterSocket, SOL_SOCKET, SO_REUSEADDR, (char *)optval, sizeof(int));
	int error = bind(masterSocket, (struct sockaddr *)&serverIPAddress, sizeof(serverIPAddress));
	if(error){
		perror("bind");
		exit(-1);
	}
	error = listen(masterSocket, QueueLength);
	if(error){
		perror("listen");
		exit(-1);
	}
	while(1){
		struct sockaddr_in clientIPAddress;
		int alen = sizeof(clientIPAddress);
		int slaveSocket = accept(masterSocket, (struct sockaddr *)&clientIPAddress, (socklen_t*)&alen);
		if(slaveSocket < 0){
			perror("accept");
			exit(-1);
		}
		serveFile(slaveSocket, argv[0]);
		close(slaveSocket);
	}
}
