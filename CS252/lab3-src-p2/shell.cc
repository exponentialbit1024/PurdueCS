#include "command.hh"
#include <signal.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <wait.h>

int yyparse(void);

extern "C" void ctrlC(int sig){
	printf("%d\n", sig);
	Command::_currentCommand.prompt();
}

extern "C" void zombieKill(int sig){
	int pid = wait3(0, 0, NULL);
	while(waitpid(-1, NULL, WNOHANG) > 0);
//	printf("%d exited\n", pid);
}

int main() {
	struct sigaction sigCtrlC;
	sigCtrlC.sa_handler = ctrlC;
	sigemptyset(&sigCtrlC.sa_mask);
	sigCtrlC.sa_flags = SA_RESTART;
	int error = sigaction(SIGINT, &sigCtrlC, NULL);
	if(error){
		perror("sigaction");
		exit(-1);
	}
	struct sigaction sigzmb;
	sigzmb.sa_handler = zombieKill;
	sigemptyset(&sigzmb.sa_mask);
	sigzmb.sa_flags = SA_RESTART;
	int error2 = sigaction(SIGCHLD, &sigzmb, NULL);
	if(error2){
		perror("sigaction");
		exit(-1);
	}
	Command::_currentCommand.prompt();
	yyparse();
}
