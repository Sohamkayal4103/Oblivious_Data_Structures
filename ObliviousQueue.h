#ifndef OBLIVIOUSQUEUE_H
#define OBLIVIOUSQUEUE_H

#include <string>
using namespace std;

class ObliviousQueue {
public:
    ObliviousQueue();
    void Enqueue(const string &data);
    string Dequeue();
private:
    // (Implementation details hidden in .cpp file.)
};

#endif // OBLIVIOUSQUEUE_H
