#include <iostream>
#include <unistd.h>
#include <vector>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdlib>
#include <ctime>
#include <cstring>

#include "rsleep.cpp"

int pv = 3;
void handler(int) {
    pv--;
    std::cout << "Nombre de points de vie restants : " << pv << " pour :" << getpid()<< std::endl;
    if (pv == 0) {
        std::cout << getpid() << " est mort !" << std::endl;
        exit(1);
    }
}
void attaque (pid_t adversaire) {
    struct sigaction sa = {0};
    sigset_t mask;
    sigfillset(&mask);
    sigdelset(&mask, SIGINT);
    sa.sa_handler = &handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    if (kill(adversaire, SIGINT) == -1) {

        exit(0);
    }
    randsleep();
}

void defense() {
    struct sigaction sa = {0};
    sa.sa_handler = SIG_IGN ;
    sigaction(SIGINT, &sa, NULL);
    randsleep();
}

void combat(pid_t adversaire) {
    while(true) {
        attaque(adversaire);
        defense();
    }
}

int main() {
    pid_t vador = getpid(); //père
    std::cout << "Vador " << vador <<" : 'Je suis ton père..'" << std::endl;
    pid_t luke = fork(); // Fils
    std::cout << "Luke "<< luke <<  " : 'NOOOOOON' " << std::endl;
    if (luke != 0) {
        combat(luke);
    } else {
        combat(vador);
    }
   

    return 0;
}