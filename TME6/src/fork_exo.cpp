#include <iostream>
#include <unistd.h>
#include <vector>
#include <sys/types.h>
#include <sys/wait.h>
int main () {
	const int N = 3;
	int nb_fils = 0;
	std::cout << "main pid=" << getpid() << std::endl;
	pid_t pidf = fork();
	for (int i=1, j=N; i<=N && j==N && pidf==0 ; i++ ) { // fils de main
		if (pidf != 0){ //père
			nb_fils++;
			break;
		} else { //fils
			nb_fils = 0;
		}
		std::cout << " i:j " << i << ":" << j << std::endl;
		for (int k=1; k<=i && j==N ; k++) { // petit-fils de main
			if ( fork() == 0) {
				nb_fils =0;
				j=0;
				std::cout << " k:j " << k << ":" << j << std::endl;
			} else nb_fils++;
		}

	}
	for (int j =0; j< nb_fils; j++){
		int i  = wait(NULL);
		if (i == -1){
			std::cerr << "Trop de wait :(" << std::endl;
		}
	}
	if (wait(NULL) == -1)
		std::cout << "J'ai fini d'attendre mes fils :)" << std::endl;
	return 0;
}
