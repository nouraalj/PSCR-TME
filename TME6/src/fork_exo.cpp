#include <iostream>
#include <unistd.h>
#include <vector>
#include <sys/types.h>
#include <sys/wait.h>
int main () {
	const int N = 3;
	int nb_child = 0;
	std::cout << "main pid=" << getpid() << std::endl;
	pid_t pidf = fork();
	for (int i=1, j=N; i<=N && j==N && pidf==0 ; i++ ) { // fils de main
		if (pidf != 0){ //père
			nb_child++;
			break;
		} else { //fils
			nb_child = 0;
		}
		std::cout << " i:j " << i << ":" << j << std::endl;

		for (int k=1; k<=i && j==N ; k++) { // petit-fils de main
			if ( fork() == 0) {
				nb_child =0;
				j=0;
				std::cout << " k:j " << k << ":" << j << std::endl;
			} else nb_child++;
		}

	}
	for (int j =0; j< nb_child; j++){
		wait(NULL);
		if (wait(NULL) == -1){
			std::cerr << "Trop de wait \n" << std::endl;
		}
	}
	if (wait(NULL) != -1)
		std::cerr << "Il en reste \n";
	return 0;
}
