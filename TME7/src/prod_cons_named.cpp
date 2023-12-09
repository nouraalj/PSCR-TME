#include "Stack.h"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <vector>

#define N 3
#define M 5

using namespace std;
using namespace pr;

void handler(int sig){
    if (sig == SIGINT){
        cout << "Received Ctrl-C, consumer" << getpid() <<  "stopped" << endl;
        kill(getpid(), SIGTERM);
    }
}
void producteur (Stack<char> * stack) {
	char c ;
	while (cin.get(c)) {
		stack->push(c);
	}
    cout<< "produced"<< endl;

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

	//créer le segment de mémoire partagée
	int shm_fd = shm_open("/myshm", O_CREAT | O_EXCL | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(1);
    }
    cout<< "shm created"<< endl;
    //alllouer au segment une taille sur la mémoire pour stocker une stack :
    if (ftruncate(shm_fd, sizeof(Stack<char>)) == -1) {
        perror("ftruncate");
        exit(1);
    }
    cout<< "shm memory allocated"<< endl;

    // on map (attache) le segment de mémoire partagé (renvoie l'adresse du segment)
    void *addr = mmap(NULL, sizeof(Stack<char>), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (addr == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }
    cout<< "shm attached"<< endl;


    vector<pid_t> producers, consumers;


	Stack<char> * s = new (addr) Stack<char>();
    
    for (int i = 0; i < N; ++i) {
        pid_t pp = fork();
        if (pp==0) {
            producteur(s);
            return 0;
        }
        producers.emplace_back(pp);
    }
    
    for (int i = 0; i < N; ++i) {
        pid_t pc = fork();
        if (pc==0) {
            consomateur(s);
            return 0;
        }
        consumers.emplace_back(pc);
    }

    for(pid_t pid :producers){
        waitpid(pid, NULL, 0);
    }

    for(pid_t pid : consumers){
        waitpid(pid, NULL, 0);
    }
    
	s->~Stack();
	if(munmap(addr,sizeof(Stack<char>))!=0){
		perror("munmap");
		exit(1);
	};

	if (shm_unlink("/myshm") == -1) {
        perror("shm_unlink");
        exit(1);
    }
	return 0;
}

