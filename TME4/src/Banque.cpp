#include "Banque.h"

#include <iostream>

using namespace std;

using namespace pr;

void Banque::transfert(size_t deb, size_t cred, unsigned int val) {
	unique_lock<mutex> l(m); //Q9
	Compte & debiteur = comptes[deb];
	Compte & crediteur = comptes[cred];
	/* Q6 if (deb<cred){
		debiteur.lock();
		crediteur.lock();
	}
	else if (deb>cred){
		crediteur.lock();
		debiteur.lock();
	}
		else{
		//deb=cred => meme compte, on ne transfère rien
		return;
	}*/
	if (debiteur.debiter(val)) {
		crediteur.crediter(val);
	}
	debiteur.unlock();
	crediteur.unlock();
}
size_t Banque::size() const {
	unique_lock<mutex> l(m);
	return comptes.size();
}
bool Banque::comptabiliser (int attendu) const {
	unique_lock<mutex> l(m);
	int bilan = 0;
	int id = 0;
	for (const auto & compte : comptes) {
		if (compte.getSolde() < 0) {
			cout << "Compte " << id << " en négatif : " << compte.getSolde() << endl;
		}
		bilan += compte.getSolde();
		id++;
	}
	if (bilan != attendu) {
		cout << "Bilan comptable faux : attendu " << attendu << " obtenu : " << bilan << endl;
	}
	return bilan == attendu;
}
void Banque::afficher() const
	{
		// std::unique_lock<std::mutex> g(m_banque);
		int id = 0;
		for (const auto &compte : comptes)
		{
			cout << "Compte " << id << " : " << compte.getSolde() << endl;
			++id;
		}
}
