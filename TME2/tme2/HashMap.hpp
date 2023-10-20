#include <ostream>
#include <cstddef>
#include <vector>
#include <forward_list>
using namespace std;
namespace pr
{
    template <typename K, typename V>

    class HashMap
    {
    public:
        class Entry
        {
        public:
            const K key;
            V value;
            Entry(const K &k, const V &v) : key(k), value(v) {}
        };


    private:
        typedef std::vector<std::forward_list<Entry>> buckets_t;
        buckets_t buckets;
        size_t sz;

    public:
        HashMap(size_t size) : buckets(size), sz(0) {}
        V *get(const K &k)
        {
            size_t i = (std::hash<K>()(k)) % buckets.size();
            for (auto &elt : buckets[i])
            {
                if (elt.key == k)
                {
                    return &elt.value;
                }
            }
            return nullptr;
        }
        bool put(const K &k, const V &v)
        {
            size_t i = (std::hash<K>()(k)) % buckets.size();
            for (auto &elt : buckets[i])
            {
                if (elt.key == k)
                {
                    elt.value = v;
                    return true;
                }
            }
            sz++;
            buckets[i].emplace_front(k, v);
            return false;
        }
        size_t size() const { return sz; }

        class Iterator
        {
            typename buckets_t::Iterator buckend;            // itérateur positionné sur buckets.end()
            typename buckets_t::Iterator vit;                // buckets_t &buck : itérateur sur la table de buckets
            typename std::forward_list<Entry>::Iterator lit; // itérateur sur la liste qui pointe l'élément cur de la liste
        public:
            // cstor :
            Iterator(buckets_t::Iterator buckend, buckets_t::Iterator vit, std::forward_list<Entry>::Iterator lit)
                : buckend(buckend), vit(vit), lit(lit) {}

            Iterator &operator++()
            {
                ++lit;                 // on se décale dans la liste
                if (lit == vit->end()) // buck[index].end() si on arrive à la fin de la liste
                    ++vit;             // index++ on passe passe au bucket suivant
                while (vit->empty() && vit != buckend)
                {          // for(;index < buck.size() && buck[index]empty(); ++index)
                    ++vit; // on continue tant que les buckets sont vides
                }
                if (vit != buckend) //on n'a pas déborder :
                { // if index<buck.size()   lit = buck[index].begin();
                    lit = vit->begin(); //on positionne lit au début de la liste de ce bucket non vide
                }
                return *this;
            }
            bool operator!=(const Iterator &other)
            {
                return (vit != other.vit) || (lit != other.lit) ; //|| (&buck != &other.buck)
            }
            Entry &operator*()
            {
                return *lit;
            }
            /* avec indice*/
            Iterator begin()
            {
               typename buckets_t::iterator vit = buckets.begin();
                while (vit->empty && vit != buckets.end()){
                    ++vit;
                }
                if (vit != buckets.end()){
                    return Iterator(buckets.end(), vit, vit->begin());
                } 
                else {return end();}
            }
            Iterator end()
            {
                return Iterator(buckets.size(), buckets.end(), buckets);
            }
        };
    };

}