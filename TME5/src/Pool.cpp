#include "Pool.h"

using namespace std;

namespace pr {
    Pool::Pool(int qsize) : queue(qsize) {}
    void poolWorker(Queue<Job> &queue){
        while(true){
            Job *j =queue.pop();
            if (j=nullptr) break;
            j->run();
            delete j;
        }
    }

    void Pool::start(int nbthreads){
        threads.reserve(nbthreads);
        for(int i = 0; i<nbthreads;++i){
            threads.emplace_back(poolWorker, ref(queue));
        }

    }
    void Pool::submit(Job *j){
        queue.push(j);
    }

    void Pool::stop(){
        queue.setBlocking(false);
        for(auto &t: threads){
            t.join();
        }
        threads.clear();
    }
    Pool::~Pool(){
        stop();
    }
}