#include <iostream>
#include <csignal>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int wait_till_pid(pid_t pid) {
    int status;
    pid_t child_pid;
    while((child_pid = wait(&status)) > 0) { //on attend que le procs fils se terminent
        if (child_pid  == pid) { //c'est le bon fils qu'on attendait
            return pid; 
        }
    }
    //sinon il y a eu une erreur :
    return -1;
}

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        sleep(5);
        std::cout << "fin proc fils" << std::endl;
    } else if (pid > 0) {
        std::cout << "le pere attend son fils" << std::endl;

        int result = wait_till_pid(pid);

        if (result == pid) {
            std::cout << "le processus fils s'est terminé avec le statut : " << WEXITSTATUS(result) << std::endl;
        } else {
            std::cout << "erreur lors de l'attente" << std::endl;
        }
    }
    return 0;
}
