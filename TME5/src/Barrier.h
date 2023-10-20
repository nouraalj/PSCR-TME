#include <mutex>
#include <condition_variable>
using namespace std;


class Barrier{
    mutex m;
    int cpt;
    const int N;
    condition_variable cv;
    public:
        Barrier(int N):cpt(0),N(N){}
        void done(){
            unique_lock<mutex> l(m);
            cpt++;
            if (cpt == N){
                cv.notify_all();
            }
        }
        void waitFor(){
            unique_lock<mutex> l(m);
            while(cpt != N){
                cv.wait(l);
            }
        }
};