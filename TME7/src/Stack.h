#pragma once

#include <cstring> // size_t,memset
#include <semaphore.h>
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
		sem_init(&semPop, 1, 0);
		}

	~Stack(){
		sem_destroy(&semMutex);
		sem_destroy(&semPush);
		sem_destroy(&semPop);
	}

	T pop () {
		// bloquer si vide
		sem_wait(&semPop);
		sem_wait(&semMutex);
		T toret = tab[--sz];
		sem_post(&semMutex);
		sem_post(&semPush);
		return toret;
	}

	void push(T elt) {
		//bloquer si plein
		sem_wait(&semPush);
		sem_wait(&semMutex);
		tab[sz++] = elt;
		sem_post(&semMutex);
		sem_post(&semPop);
	}
};

}
