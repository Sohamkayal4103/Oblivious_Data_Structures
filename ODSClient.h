#ifndef ODSCLIENT_H
#define ODSCLIENT_H

#include <unordered_map>
using namespace std;

class ODSClient {
public:
    // Used for oblivious priority queue (integer payloads)
    unordered_map<int, int> intStorage;
    
    void Start() { }
    
    int AccessReadInt(int id) {
        if (intStorage.find(id) != intStorage.end())
            return intStorage[id];
        return -1;
    }
    
    void AccessWriteInt(int id, int key) {
        intStorage[id] = key;
    }
    
    void AccessInsertInt(int id, int key) {
        intStorage[id] = key;
    }
    
    void AccessDelInt(int id) {
        intStorage.erase(id);
    }
    
    void Finalize(int root, int padVal) {
        // Stub: reassign positions and add dummy operations as needed.
    }
};

// Template client for objects (used by the AVL-based map)
template <typename T>
class ODSClientObj {
public:
    unordered_map<int, T> storage;
    
    void Start() { }
    
    T AccessRead(int id) { 
        return storage[id]; 
    }
    
    void AccessWrite(int id, const T &obj) { 
        storage[id] = obj; 
    }
    
    void AccessInsert(int id, const T &obj) { 
        storage[id] = obj; 
    }
    
    void Finalize(int root, int padVal) {
        // Stub for padding.
    }
};

#endif // ODSCLIENT_H