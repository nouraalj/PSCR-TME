#include "Banque.h"
#include <iostream>
using namespace std;
const int NB_THREAD = 10;
const int NB_COMPTES = 10;
const int SOLDEINITIAL = 500;

void transaction(int index, pr::Banque &b){
		std::cout << "started "<< index << endl;
        for(int ind=0; ind<10000; ind++){
            int i = rand()%b.size();
            int j = rand()%b.size();
            int m = rand()%100+1;
            b.transfert(i,j,m);
            //std::this_thread::sleep_for(std::chrono::milliseconds(rand()%21)); 
        }
		//std::cout << "finished "<< index << endl;
}

int main () {
	vector<thread> threads;
	vector<thread> comptables;

	// TODO : creer des threads qui font ce qui est demandé
	
	threads.reserve(NB_THREAD);
	pr::Banque b(NB_COMPTES, SOLDEINITIAL);
	b.afficher();
    for(int i=0; i<NB_THREAD; i++){
		threads.emplace_back(transaction, i, ref(b));
		//std::cout << "created "<< i << endl;
		comptables.emplace_back(&pr::Banque::comptabiliser, ref(b), b.size()*SOLDEINITIAL);
	}
	b.comptabiliser(b.size() * SOLDEINITIAL);
	for (auto & t : threads) {
		t.join();
	}
	for (auto & t : comptables) {
		t.join();
	}
	b.afficher();

	// TODO : tester solde = NB_THREAD * JP
	
	
	return 0;
}
