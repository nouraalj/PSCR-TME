#include <cstddef>
#include <vector>
#include <forward_list>

/*Boucle infinie avec les itérateurs ?
TODO : voir pas à pas l'exécution du code pour voir pourquoi l'itérateur boucle vers l'infini*/
/*essayer de faire avec un itérateur sur le vecteur plutôt qu'un index*/
using namespace std;
namespace pr {

template <typename K, typename V>

class HashMap{
    public :
    class Entry{
        public:
        const K key;
        V value;
        Entry(const K& key, const V& value):key(key), value(value){}
        
    };
    typedef std::vector <std::forward_list<Entry>> buckets_t;

    class Iterator{
        buckets_t& it_buckets ;
        typename std::forward_list<Entry>::iterator lit;
        size_t index;


                
        public :
        Iterator(size_t index, typename std::forward_list<Entry>::iterator lit, buckets_t & buck):index(index),lit(lit),it_buckets(buck){}
        Iterator(HashMap &ht, int end):it_buckets(ht.bucket){  //Constructeur d'un itérateur end
            index = -1;
            lit = it_buckets[0].end();
        }   

        /*

        Tentative qui ne marche pas
        Iterator& operator++(){
Problème ici
            if(lit == it_buckets[index].end()){
                advance();
                
                if(lit!= it_buckets[index].end()){
                    ++lit;
                }
            }
            else{
                ++lit;
                if(lit == it_buckets[index].end()){
                    advance();
                }
            }
            return *this;
        }
    */
        Iterator & operator++(){
            ++lit;
            if (lit == it_buckets[index].end()){
                index++;
                for ( ; index < it_buckets.size()&& it_buckets[index].empty();++index){
                    /*NOP*/
                }
                if (index < it_buckets.size()) lit = it_buckets[index].begin();
            }
            return *this;
        }


        Entry& operator*(){
            return *lit;
        }
        bool operator!=(Iterator& other){
            return (index != other.index) || (lit != other.lit);    
        }
    };

    private :
    buckets_t bucket ;
    size_t sz;                    //Nombre d'entrées
    
    public :
    HashMap(size_t szb) : bucket(szb){
        sz = 0;
        for (size_t i = 0 ; i < sz; ++i){
            bucket.push_back(std::forward_list<Entry>());
        }
    }
    // (Les mécanismes de la classe canonique sont implémentés par défaut par le compilateur, pas besoin de les réécrire.)

    /*Fonctions pour l'itérateur*/

/*Version qui ne marche pas
    Iterator begin(){
        return Iterator(*this);
    }
*/
/*Correction*/

    Iterator begin(){
        for(int index = 0; index < bucket.size(); ++index ){
            if (!bucket[index].empty){
                return Iterator(index,bucket[index].begin(),bucket);
            }
        }
        return end();
    }

    Iterator end(){
        return Iterator(bucket.size(),bucket[0].end(),bucket);//On prend bucket[0].end() pour un nullptr
    }

    /*Fonction qui rend l'adresse de la valeur associée à la clé key si on la trouve, nullptr sinon*/
    V* get (const K & key){
        size_t ind = (std::hash<K>() (key)) % bucket.size();    //Hasher standard

        /*Trouver le mot dans la hashmap*/
        for (auto& e : bucket[ind]){
            if (e.key == key){
                return &e.value;
            }
        }       
        return nullptr;
    }
    /*Fonction qui ajoute l'association (key, value) à la table. 
    * La fonction rend vrai si la valeur associée à key a été mise à jour dans la table, 
    * et faux si on a réalisé une insertion (la clé n'était pas encore dans la table).*/
    bool put (const K & key, const V value){
        size_t ind = std::hash<K>() (key) % bucket.size();

        for(auto & e : bucket[ind]){
		    if (e.key == key){
                e.value = value;
                return true;
            }
    	}
        /*On ne l'a pas trouvé dans le bucket, il faut créer l'association dans la table*/
        bucket[ind].emplace_front(key,value);           //emplace évite de créer un temporaire
        ++sz;                 //La taille de la Hashtable augmente
        return false;           //On a créé une insertion
    }
    /*Fonction qui indique la taille de la hashtable (nombre d'entrées effectives dedans)*/
    size_t size() const{return sz;}
    };

    
}