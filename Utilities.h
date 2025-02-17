#ifndef UTILITIES_H
#define UTILITIES_H

#include <cmath>

// Global ID generator (returns a new unique ID each call)
inline int nextid() {
    static int id = 1;
    return id++;
}

inline int floorLog2(int x) {
    return static_cast<int>(floor(log2(x)));
}

#endif // UTILITIES_H