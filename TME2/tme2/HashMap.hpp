#include <ostream>
#include <cstddef>
#include <vector>
#include <forward_list>

namespace pr{
    template <typename K, typename V>

    class HashMap{
        public: 
            class Entry{
                public:
                    const K key;
                    V value;
                    Entry(const K &k, const V& v):key(k), value(v){}
            };
        private:
            typedef std::vector<std::forward_list<Entry>> buckets_t;
            buckets_t buckets;
            size_t sz;
        public:
            HashMap(size_t size): buckets(size), sz(0) {}
            V* get(const K &k){
                size_t i = (std::hash<K>()(k))%buckets.size();
                for(auto &elt : buckets[i]){
                    if (elt.key == k){
                        return &elt.value;
                    }
                }
                return nullptr;
            }
            bool put(const K &k, const V &v){
                size_t i = (std::hash<K>()(k))%buckets.size();
                for(auto &elt : buckets[i]){
                    if (elt.key == k){
                        elt.value = v;
                        return true;
                    }
                    
                }
                sz++;
                buckets[i].emplace_front(k,v);
                return false;
            }
            size_t size() const { return sz;}
            
            class iterator{
                size_t index;
                typedef buckets_t::iterator buckend; //itérateur positionné sur buckets.end()
                typedef buckets_t::iterator vit; //buckets_t &buck : itérateur sur la table de buckets 
                typedef std::forward_list<Entry>::iterator lit; //itérateur sur la liste qui pointe l'élément cur de la liste
                public:
                //cstor :
                iterator(buckets_t::iterator buckend,buckets_t::iterator vit, std::forward_list<Entry>::iterator lit)
                :buckend(buckend), vit(vit), lit(lit){}
                
                iterator & operator++() {
                    lit++ //on incrémente la liste
                    if(lit==vit->end()) // buck[index].end() si on arrive à la fin de la liste
                        vit++; //index++ on passe passe au bucket suivant
                        while(vit->empty && vit!= buckend){ //for(;index < buck.size() && buck[index]empty(); ++index)
                            vit++; //nop
                        }
                        if (vit != buckend){ //if index<buck.size()   lit = buck[index].begin();
                            lit = vit->begin();
                        }
                        //return *this;
                }
                bool operator!=(const iterator &other){
                    return index!= other.index || lit != other.lit || &buck != &other.buck;
                }
                Entry & operator* (){
                    return *lit;
                }

                iterator begin(){
                    //on cherche le premier bucket non vide :
                    for(size_t i =0; i<buckets_t.size(); i++){
                        if(!buckets[i].empty())
                            return iterator(i, buckets[i].begin(), buckets);
                    }
                    return end();
                }
                iterator end(){
                    return iterator(bucket_size(), buckets[0].end(),buckets)
                }
                      
            };
            
    };
    
}