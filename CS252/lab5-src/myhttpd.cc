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
#include <sys/wait.h>
#include <pthread.h>
#include <sstream>
#include <sys/stat.h>
#include <dirent.h>
#include <vector>
#include <algorithm>
#include <dlfcn.h>
#include <link.h>
#include <errno.h>
#include <sstream>
#include <fstream>

using namespace std;

int QueueLength = 15;

const char *secret = "5J1vCTsHxe9X79PyLDjQhZAtCYJPK8us0A9xnjjQ";
const char *currPath;
bool production = true;
int totalRequests = 0;
time_t startTime;
typedef void (*httprunfunc)(int ssock, const char *querystring);

bool date_comparator(std::string f1, std::string f2){
	struct stat t_stat1;
	struct stat t_stat2;
	stat(f1.c_str(), &t_stat1);
	stat(f2.c_str(), &t_stat2);
	if(t_stat1.st_ctime - t_stat2.st_ctime < 0){
		return false;
	}else{
		return true;
	}
}

int check_dir(const char *path){
	struct stat path_stat;
	stat(path, &path_stat);
	return S_ISREG(path_stat.st_mode);
}

int check_image(std::string path){
	return path.find(".");
}

void serve_dir(std::string usbpath, int fd){
	//std::cout << "testing path" << "\n";
	//std::cout << usbpath << "\n";
	if(check_image(usbpath) != -1){
		write(fd, "HTTP/1.1 200 Document follows", 29);
		write(fd, "\r\n", 2);
		write(fd, "Server: CS 252 lab5", 19);
		write(fd, "\r\n", 2);
		write(fd, "Content-type: ", 14);
		write(fd, "image/ico", 9);
		write(fd, "\r\n", 2);
		write(fd, "\r\n", 2);
		write(fd, "\r\n", 2);
		return;
	}
	int qfind = usbpath.find("?");
	std::string rdirpath;
	std::string sortFlag;
	if(qfind == -1){
		rdirpath.assign(usbpath);
	}else{
		rdirpath = usbpath.substr(0, qfind);
		sortFlag = usbpath.substr(qfind + 1, usbpath.length());
	}
	int endSlashBugFlag = 0;
	if(rdirpath.at(rdirpath.length() - 1) == '/'){
		endSlashBugFlag = 1;
		rdirpath.replace(rdirpath.length() - 1, 1, "");
	}
	//std::cout << "rdir: " + rdirpath << "\n";
	//std::cout << sortFlag << "\n";
	int ascSort = sortFlag.find("D=0");
	int dSort = sortFlag.find("d=1");
	//printf("sort asc : %d\n", ascSort);
	//printf("d sort : %d\n", dSort);
	//std::cout << rdirpath << "\n";
	DIR *serveDir = opendir(rdirpath.c_str());
	struct dirent *pDirent;
	std::vector<std::string> sortedFiles;
	while((pDirent = readdir(serveDir)) != NULL){
		if(strcmp(pDirent -> d_name, ".") != 0 && strcmp(pDirent -> d_name, "..") != 0 && (pDirent -> d_name[0] != '.')){
			std::string fname = pDirent -> d_name;
			sortedFiles.push_back(rdirpath + "/" + fname);
		}
	}
	closedir(serveDir);
	std::string dirhtmlStr("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 3.2 Final//EN\"><html><head><title> Index of");
	dirhtmlStr.append(rdirpath);
	dirhtmlStr.append("</title></head><body><h1> Index of");
	dirhtmlStr.append(rdirpath);
	dirhtmlStr.append("</h1><table>");
	//std::cout << dirhtmlStr << "\n";
	if(ascSort != -1){
		//ascending sort
		if(dSort != -1){
			std::sort(sortedFiles.begin(), sortedFiles.end(), date_comparator);
		}else{
			std::sort(sortedFiles.begin(), sortedFiles.end());
		}
	}else{
		//descending sort
		if(dSort != -1){
			std::sort(sortedFiles.rbegin(), sortedFiles.rend(), date_comparator);
		}else{
			std::sort(sortedFiles.rbegin(), sortedFiles.rend());
		}
	}
	for(std::vector<int>::size_type i = 0; i != sortedFiles.size(); i++){
		dirhtmlStr.append("<tr><th colspan=5><a href=\"");
		int fsf = sortedFiles[i].find_last_of("/");
		if(endSlashBugFlag == 0){
			dirhtmlStr.append(rdirpath.substr(rdirpath.find_last_of("/") + 1, rdirpath.length()) + "/" + sortedFiles[i].substr(fsf + 1, sortedFiles[i].length()));
		}else{
			dirhtmlStr.append(sortedFiles[i].substr(fsf + 1, sortedFiles[i].length()));
		}
		dirhtmlStr.append("\"><h4>");
		dirhtmlStr.append(sortedFiles[i].substr(fsf + 1, sortedFiles[i].length()));
		dirhtmlStr.append("</h4></a></th></tr>");
	}
	write(fd, "HTTP/1.1 200 Document follows", 29);
	write(fd, "\r\n", 2);
	write(fd, "Server: CS 252 lab5", 19);
	write(fd, "\r\n", 2);
	write(fd, "Content-type: ", 14);
	write(fd, "text/html", 10);
	write(fd, "\r\n", 2);
	write(fd, "\r\n", 2);
	write(fd, dirhtmlStr.c_str(), dirhtmlStr.size());
	write(fd, "\r\n", 2);
	return;
}

void serveFile(int fd){
	std::string secretStr(secret);
	const int MaxName = 1024;
	char name[MaxName + 1];
	int nameLength = 0;
	int n;

	unsigned char newChar;
	unsigned char lastChar = 0;
	while(nameLength < MaxName && (n = read(fd, &newChar, sizeof(newChar) )) > 0){
		if(lastChar == '\015' && newChar == '\012'){
			n = read(fd, &newChar, sizeof(newChar));
			if(n > 0 && newChar == '\015'){
				n = read(fd, &newChar, sizeof(newChar));
				if(n > 0 && newChar == '\012'){
					break;
				}
			}
		}
		name[nameLength] = newChar;
		nameLength++;
		lastChar = newChar;
	}
	
	name[nameLength] = '\0';
	//printf("request: %s\n", name);
	std::string requestStr(name);
	if(requestStr.length() == 0){
		return;
	}
	int pathindex = requestStr.find("/");
	std::string insecStr = requestStr.substr(pathindex + 1, pathindex + 36);
	
	int pathc = pathindex;
	while(requestStr.at(pathc) != ' '){
		pathc++;
	}
	
	std::string pathStr = requestStr.substr(pathindex + 1, pathc - 5);

	std::string logStr = insecStr;
	logStr.append("\t\t");
	if(pathStr.length() == 0){
		logStr.append("index.html");
	}else{
		logStr.append(pathStr);
	}
	printf("%s\n", logStr.c_str());
	FILE *logfp = fopen("./log", "a+");
	fprintf(logfp, (logStr + "\n").c_str());
	fclose(logfp);

	int secretCompare = insecStr.compare(secretStr);
	
	if(!secretCompare || production){
		char * rpath = (char *)malloc(1024);
		realpath(currPath, rpath);
		std::string rpathstr(rpath);
		free(rpath);
		int lastsl = rpathstr.find_last_of('/');
		std::string rdirpath = rpathstr.substr(0, lastsl + 1);

		int indexpathcmp = secretStr.compare(pathStr);
		std::string contentTypeStr;
		int imageFileFlag = 0;
		if(!indexpathcmp){
			rdirpath.append("http-root-dir/htdocs/index.html");
			contentTypeStr = "text/html";
		}else{
			if(pathStr.length() == 0){
				rdirpath.append("http-root-dir/htdocs/index.html");
				contentTypeStr = "text/html";
			}else{
				rdirpath.append("http-root-dir/htdocs/");
			}
			int specPathind = pathStr.find_last_of(" ");
			std::string filePath = pathStr.substr(specPathind + 1, pathStr.length());
			//std::cout << "filepath: " + filePath << "\n";
		
			int cgifind = filePath.find("cgi-bin");
			//printf("cgi-find : %d\n", cgifind);
			totalRequests++;
			if(cgifind != -1){
				int sfind = filePath.find("/");
				std::string scriptName = filePath.substr(sfind + 1, filePath.length());
				//std::cout << scriptName << "\n";
				int sanqf = scriptName.find("?");
				std::string sanSn;
				std::string qrs;

				std::string rspath = rdirpath.substr(0, rdirpath.length() - 2);
				std::string cgRootPath = rspath.substr(0, rspath.find_last_of("/"));
				cgRootPath.append("/");
				
				if(sanqf != -1){
					sanSn = scriptName.substr(0, sanqf);
					qrs = scriptName.substr(sanqf + 1, scriptName.length());
				}else{
					sanSn.assign(scriptName);
				}
				
				int findso = sanSn.find(".so");
				if(findso != -1){
					std::cout << cgRootPath + sanSn << "\n";
					void *lib = dlopen((cgRootPath + "cgi-src/" +sanSn).c_str(), RTLD_LAZY);
					if(lib == NULL){
						fprintf(stderr, "binary not found\n");
						perror("dlopen");
						exit(1);
					}
					httprunfunc injectrun;
					injectrun = (httprunfunc) dlsym(lib, "httprun");
					if(injectrun == NULL){
						perror("dlsym: httprun not found:");
						exit(1);
					}
					injectrun(fd, qrs.c_str());
					return;
				}

				int tempout = dup(1);

				std::cout << cgRootPath << "\n";

				int subret = fork();
				if(subret == 0){
					setenv("REQUEST_METHOD", "GET", 1);
					setenv("QUERY_STRING", qrs.c_str(), 1);
					char *procArgs[3];
					procArgs[0] = strdup((char *)(cgRootPath + "cgi-bin/" + sanSn).c_str());
					procArgs[1] = (char *)"test args";
					procArgs[2] = NULL;
					dup2(fd, 1);
					write(fd, "HTTP/1.1 200 Document follows", 29);
					write(fd, "\r\n", 2);
					write(fd, "Server: Server-Type", 20);
					write(fd, "\r\n", 2);
					execvp(procArgs[0], procArgs);
				}else if(subret < 0){
					perror("fork");
					exit(-1);
				}else{
					waitpid(subret, NULL, 0);
					write(fd, "\r\n", 2);
					write(fd, "\r\n", 2);
					write(fd, "\r\n", 2);
					dup2(tempout, 1);
					close(tempout);
					return;
				}
			}
			int statfind = filePath.find("stat");
			if(statfind != -1){
				std::string stathtmlStr("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 3.2 Final//EN\"><html><head><title> Server Stats</title></head><body><h3> Server Stats </h3><h3> Name: Siddharth Shah </h3><h3> Server Uptime: ");
				time_t endTime = time(0);
				double diff_t = difftime(endTime, startTime);
				printf("uptime : %f\n", diff_t);
				std::ostringstream ss;
				ss << diff_t;
				stathtmlStr.append(ss.str());
				stathtmlStr.append("seconds</h3><h3>Total Number of Requests: ");
				printf("total request: %d\n", totalRequests);
				std::ostringstream ss2;
				ss2 << (long) totalRequests;
				stathtmlStr.append(ss2.str());
				stathtmlStr.append("</h3>");
				stathtmlStr.append("</body></html>");
				write(fd, "HTTP/1.1 200 Document follows", 29);
				write(fd, "\r\n", 2);
				write(fd, "Server: CS 252 lab5", 19);
				write(fd, "\r\n", 2);
				write(fd, "Content-type: ", 14);
				write(fd, "text/html", 10);
				write(fd, "\r\n", 2);
				write(fd, "\r\n", 2);
				write(fd, stathtmlStr.c_str(), stathtmlStr.length());
				write(fd, "\r\n", 2);
				return;
			}
		
			int logfind = filePath.find("logs");
			if(logfind != -1){
				std::string loghtmlStr("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 3.2 Final//EN\"><html><head><title>Server Logs</title></head><body><h3>Server Log</h3>");
				ifstream logF;
				std::string lLine;
				logF.open("log", ios::in | ios::binary);
				if(logF.is_open()){
					while(getline(logF, lLine)){
						loghtmlStr.append("<h5>");		
						loghtmlStr.append(lLine);
						loghtmlStr.append("\n");
						loghtmlStr.append("</h5>");
					}
				}
				loghtmlStr.append("</body></html>");
				write(fd, "HTTP/1.1 200 Document follows", 29);
				write(fd, "\r\n", 2);
				write(fd, "Server: CS 252 lab5", 19);
				write(fd, "\r\n", 2);
				write(fd, "Content-type: ", 14);
				write(fd, "text/html", 10);
				write(fd, "\r\n", 2);
				write(fd, "\r\n", 2);
				write(fd, loghtmlStr.c_str(), loghtmlStr.length());
				write(fd, "\r\n", 2);
				return;
			}

			int qfp = filePath.find("?");
			int fileFlag;
			if(qfp != -1){
				fileFlag = check_dir((rdirpath + filePath.substr(0, qfp)).c_str());
			}else{
				fileFlag = check_dir((rdirpath + filePath).c_str());
			}
			rdirpath.append(filePath);
			//std::cout << rdirpath << "\n";
			//printf("fileflag : %d\n", fileFlag);
			if(!fileFlag){
				//its directory
				serve_dir(rdirpath, fd);
				return;
			}
			int extensionInd = filePath.find_last_of(".");
			std::string extensionStr = filePath.substr(extensionInd + 1, filePath.length());
			if(!extensionStr.compare("png")){
				imageFileFlag = 1;
				contentTypeStr = "image/png";
			}else if(!extensionStr.compare("gif")){
				imageFileFlag = 1;
				contentTypeStr = "image/gif";
			}else if(!extensionStr.compare("svg")){
				imageFileFlag = 1;
				contentTypeStr = "image/svg+xml";
			}
		}
		string fileLine;
		string allLines;
		ifstream indexF;
		indexF.open(rdirpath.c_str(), ios::in | ios::binary);
		if(indexF.is_open()){
			if(imageFileFlag == 1){
				std::ostringstream oss;
				oss << indexF.rdbuf();
				allLines = oss.str();
			}else{
				while(getline(indexF, fileLine)){
					allLines.append(fileLine);
				}
			}
			indexF.close();
		}else{
			write(fd, "HTTP/1.1 404 File Not Found", 22);
			write(fd, "\r\n", 2);
			write(fd, "Server: CS 252 lab5", 19);
			write(fd, "\r\n", 2);
			write(fd, "Content-type: text/plain", 24);
			write(fd, "\r\n", 2);
			write(fd, "\r\n", 2);
			write(fd, "No File Found", 13);
			return;
		}
		write(fd, "HTTP/1.1 200 Document follows", 29);
		write(fd, "\r\n", 2);
		write(fd, "Server: CS 252 lab5", 19);
		write(fd, "\r\n", 2);
		write(fd, "Content-type: ", 14);
		write(fd, contentTypeStr.c_str(), contentTypeStr.length());
		write(fd, "\r\n", 2);
		write(fd, "\r\n", 2);
		write(fd, allLines.c_str(), allLines.size());
		write(fd, "\r\n", 2);
	}
}

struct pool_struct {
	int masterSocket;
	struct sockaddr_in clientAddress;
	socklen_t alen;

}pool_struct;

pthread_mutex_t mutex;

void *loopthread(struct pool_struct *poolS){
	int masterSocket = poolS -> masterSocket;
	while(1){
		pthread_mutex_lock(&mutex);
		int slaveSocket = accept(masterSocket, (struct sockaddr *)&(poolS -> clientAddress), (socklen_t*)&(poolS -> alen));
		pthread_mutex_unlock(&mutex);
		if(slaveSocket >= 0){
			serveFile(slaveSocket);
			close(slaveSocket);
		}
	}
}

int main(int argc, char ** argv){
	currPath = strdup(argv[0]);	
	int processModeFlag = 0;
	int threadModeFlag = 0;
	int poolModeFlag = 0;
	startTime = time(0);
	for(int i = 0; i < argc; i++){
		printf("arg : %s\n", argv[i]);
		if(!strcmp(argv[i], "-f")){
			processModeFlag = 1;
		}
		if(!strcmp(argv[i], "-t")){
			threadModeFlag = 1;
		}
		if(!strcmp(argv[i], "-p")){
			poolModeFlag = 1;
		}
	}

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
		totalRequests++;
		if(slaveSocket < 0){
			perror("accept");
			exit(-1);
		}
		if(processModeFlag == 1){
			int ret = fork();
			if(ret == 0){
				serveFile(slaveSocket);
				close(slaveSocket);
				exit(0);
			}else if(ret < 0){
				perror("fork");
				exit(-1);
			}else{
				waitpid(ret, NULL, 0);
			}
		}else if(threadModeFlag == 1){
			pthread_t thread;
			pthread_attr_t attr;
			pthread_attr_init(&attr);
			pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
			pthread_create(&thread, &attr, (void *(*)(void *)) serveFile, (void *) slaveSocket);
			pthread_join(thread, NULL);
			close(slaveSocket);
		}else if(poolModeFlag == 1){
			pthread_t threads[5];
			struct pool_struct *poolS = (struct pool_struct*)malloc(sizeof(struct sockaddr *) + sizeof(int) + sizeof(socklen_t*));
			poolS -> masterSocket = masterSocket;
			poolS -> clientAddress = clientIPAddress;
			poolS -> alen = alen;
			pthread_mutex_init(&mutex, NULL);
			for(int j = 0;j < 4; j++){
				pthread_create(&threads[j], NULL, (void *(*)(void *))loopthread, (void *)poolS);
			}
			for(int k = 0; k < 4; k++){
				pthread_join(threads[k], NULL);
			}
			free(poolS);
		}else{
			serveFile(slaveSocket);
		}
		close(slaveSocket);
	}
}
