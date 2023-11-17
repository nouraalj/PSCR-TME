#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

void myexec(int argc, char **argv){
    std::cout << "argument de l'execv :" << std::endl;
    for(int i=0; argv[i]; i++){
        std::cout << "i" << argv[i] << std::endl;
    }
    if (execv(argv[0], argv) == -1){
        perror("execv");
        exit(3);
    }
}

int main(int argc, char *argv[]){
    char *chaine1[argc];
    char *chaine2[argc];
    int pos=-1;
    for(int i =0; i<argc; i++){
        if(!strcmp(argv[i], "|")){
            pos = i;
            break;
        }   else{
            chaine1[i-1] = argv[i]; //chaine avant |
        }
    }
    chaine1[i-1] = NULL;
    for(;i<argc;i++){
        chaine2[i-1] = argv[i]; //chaine après |
    }
    chaine2[i-1] =NULL;
    std::cout << chaine1 << std::endl;
    std::cout << chaine2 << std::endl;


    /*char* buf1 = const_cast<char*>(arg1);
    char* buf2 = const_cast<char*>(arg2);

    memcpy(buf1, chaine1, sizeof(chaine1));
    memcpy(buf2, chaine2, sizeof(chaine2));*/

    pid_t pid_fils;
    if ( (pid_fils = fork ( )) == -1 ){
        perror ("fork");
        exit (2);
    } 
    //creation tube
    int tube[2];
    if (pipe (tube) == -1) { 
        perror ("pipe");
        exit (1);
    }
    if (pid_fils == 0) { /* fils */
        dup2(tube[1],STDOUT_FILENO);
        close (tube[1]); close (tube[0]);
        myexec(argc, chaine1);
    } else { /*père*/
        dup2(tube[0],STDOUT_FILENO);
        close (tube[0]); close (tube[1]);
        myexec(argc, chaine2);

    }
}
