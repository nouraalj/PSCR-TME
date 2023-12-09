#include "Compte.h"
using namespace std;

namespace pr {
void Compte::crediter (unsigned int val) {
	/*On crédite la somme val au solde du compte*/
    unique_lock<recursive_mutex> g(m); //protéger l'accès au solde
    solde+=val ;
}
bool Compte::debiter (unsigned int val) {
	/*on débite val du compte seulement si le solde est assez grand*/
    unique_lock<recursive_mutex> g(m); 
    bool doit = (solde >= val);
    if (doit) {
        solde-=val ;
    }
    return doit;
}
int Compte::getSolde() const  {
    unique_lock<recursive_mutex> g(m);
    return solde;
}
// NB : vector exige Copyable, mais mutex ne l'est pas...
Compte::Compte(const Compte & other) {
    other.m.lock();
    solde = other.solde;
    other.m.unlock();
}
void Compte::lock() const {
    m.lock();
}

void Compte::unlock() const {
    m.unlock();
}

bool Compte::try_lock() const {
    return m.try_lock();
}

}
