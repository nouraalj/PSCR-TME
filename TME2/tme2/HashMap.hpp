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

                typedef buckets_t::iterator buckend; //itérateur positionné sur buckets.end()
                typedef buckets_t::iterator vit; //itérateur sur la table de buckets 
                typedef std::forward_list<Entry>::iterator lit; //itérateur sur la liste qui pointe l'élément cur de la liste
                
                //cstor :
                iterator():{}

                iterator & operator++() {}
                bool operator!=(const iterator &other)
                Entry & operator* (){}
            }
            
    };
    
}