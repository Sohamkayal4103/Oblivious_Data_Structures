#ifndef OBLIVIOUSSTACK_H
#define OBLIVIOUSSTACK_H

#include <string>
using namespace std;

class ObliviousStack {
public:
    ObliviousStack();
    void Push(const string &data);
    string Pop();
private:
    // (Implementation details are hidden in the .cpp file.)
};

#endif // OBLIVIOUSSTACK_H