#include "Stack.h"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <vector>

#define N 3
#define M 5

using namespace std;
using namespace pr;

void handler(int sig){
    if (sig == SIGINT){
        cout << "Received Ctrl-C, consumer " << getpid() <<  " stopped" << endl;
        kill(getpid(), SIGTERM);
    }
}

void producteur (Stack<char> * stack) {
	char c ;
	while (cin.get(c)) {
		stack->push(c);
	}
}

void consomateur (Stack<char> * stack) {
	while (true) {
		char c = stack->pop();
		cout << c << flush ;
	}
}

int main () {

	//mise en place du gestionnaire de signal :
    struct sigaction sa;
    sigset_t mask;
    sigfillset(&mask);
    sigdelset(&mask, SIGINT);
    sa.sa_handler = &handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);

	void* addr = mmap(NULL, sizeof(Stack<char>), PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_SHARED,-1,0);
	if (addr == MAP_FAILED){
		perror("mmap anonymous");
		exit(1);
	}
	Stack<char> * s = new (addr) Stack<char>(); //on place la stack dans la mémoire partagée
	pid_t pp = fork();
	if (pp==0) {
		producteur(s);
		return 0;
	}

	pid_t pc = fork();
	if (pc==0) {
		consomateur(s);
		return 0;
	}

	wait(0);

	s->~Stack();
	if(munmap(addr,sizeof(Stack<char>))!=0){
		perror("munmap");
		exit(1);
	};
	
	return 0;
}

