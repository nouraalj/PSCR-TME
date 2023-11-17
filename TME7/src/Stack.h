#pragma once

#include <cstring> // size_t,memset
#include <semaphore>
#include <sys/mman.h>

namespace pr {

#define STACKSIZE 100

template<typename T>
class Stack {
	T tab [STACKSIZE];
	sem_t semPop;
	sem_t semPush;
	sem_t semMutex;
	size_t sz;
public :
	Stack () : sz(0) { 
		memset(tab,0,sizeof tab) ;
		sem_init(&semMutex, 1, 1);
		sem_init(&semPush,1, STACKSIZE);
		sem_init(&semPop, 1, STACKSIZE);
		}

	~Stack(){
		sem_destroy(&semMutex);
		sem_destroy(&semPush);
		sem_destroy(&semPop);
	}

	T pop () {
		// bloquer si vide
		sem_wait()
		T toret = tab[--sz];
		return toret;
	}

	void push(T elt) {
		//bloquer si plein
		tab[sz++] = elt;
	}
};

}
