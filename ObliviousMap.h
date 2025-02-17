#ifndef OBLIVIOUSMAP_H
#define OBLIVIOUSMAP_H
#include<utility>
using namespace std;

// Node structure for the AVL-based oblivious map.
struct MapNode {
    int id;
    int key;
    int ht1;   // height of left subtree
    int ht2;   // height of right subtree
    int left;  // left child id (0 if null)
    int right; // right child id (0 if null)
};

class ObliviousMap {
public:
    ObliviousMap();
    void Insert(int key);
    MapNode Find(int key);
    void PrintInOrder(); // For demonstration
private:
    int root; // id of the root node (0 means empty)
    
    // Helper functions:
    int InsertPriv(int key, int nodeid);
    MapNode FindPriv(int key, int nodeid);
    pair<int,int> Balance(int id);
    pair<int,int> RotLC(int id);
    pair<int,int> RotRC(int id);
    pair<int,int> DbRotLC(int id);
    pair<int,int> DbRotRC(int id);
    void InOrder(int nodeid);
};

#endif // OBLIVIOUSMAP_H
