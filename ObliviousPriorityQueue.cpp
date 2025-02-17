#include "ObliviousPriorityQueue.h"
#include "ODSClient.h"
#include "Utilities.h"
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>
using namespace std;

// We simulate our heap using the ODSClient instance (for integer payloads)
static ODSClient odsPQ;
static int heapSize = 0;

// readPath() reads a root-to-leaf path from the heap (indices 1..heapSize)
vector<pair<int,int>> readPathPQ() {
    vector<pair<int,int>> path;
    int nodeid = 1;
    int level = 1;
    while (nodeid <= heapSize) {
        int key = odsPQ.AccessReadInt(nodeid);
        path.push_back({key, nodeid});
        int bit = (nodeid >> (level - 1)) & 1;
        if (bit == 0)
            nodeid = nodeid * 2;
        else
            nodeid = nodeid * 2 + 1;
        level++;
    }
    return path;
}

ObliviousPriorityQueue::ObliviousPriorityQueue() {
    heapSize = 0;
}

void ObliviousPriorityQueue::Insert(int key) {
    odsPQ.Start();
    vector<pair<int,int>> list = readPathPQ();
    int newNodeId = heapSize + 1;
    list.push_back({key, newNodeId});
    heapSize++;
    // Bubble up (here we use a max-heap condition per the pseudocode;
    // adjust comparisons if you need a min-heap)
    for (int i = list.size()-1; i >= 1; i--) {
        if (list[i].first > list[i-1].first)
            swap(list[i].first, list[i-1].first);
    }
    // Write back all nodes on the path
    for (int i = list.size()-1; i >= 0; i--) {
        odsPQ.AccessWriteInt(list[i].second, list[i].first);
    }
    int padVal = max(1, 3 * floorLog2(heapSize));
    odsPQ.Finalize(1, padVal);
}

int ObliviousPriorityQueue::ExtractMin() {
    if (heapSize == 0) return -1;
    odsPQ.Start();
    vector<pair<int,int>> list = readPathPQ();
    int minKey = list[0].first; // root key
    list[0].first = list.back().first; // replace root with last key
    heapSize--;
    list.pop_back();
    for (int i = list.size()-1; i >= 0; i--) {
        odsPQ.AccessWriteInt(list[i].second, list[i].first);
    }
    int nodeid = 1;
    while (nodeid <= heapSize) {
        int key = odsPQ.AccessReadInt(nodeid);
        int leftId = 2 * nodeid;
        int rightId = 2 * nodeid + 1;
        int lkey = (leftId <= heapSize) ? odsPQ.AccessReadInt(leftId) : INT_MAX;
        int rkey = (rightId <= heapSize) ? odsPQ.AccessReadInt(rightId) : INT_MAX;
        if (rkey < lkey) {
            if (key >= rkey) {
                odsPQ.AccessWriteInt(nodeid, rkey);
                nodeid = rightId;
            } else break;
        } else {
            if (key >= lkey) {
                odsPQ.AccessWriteInt(nodeid, lkey);
                nodeid = leftId;
            } else break;
        }
        odsPQ.AccessWriteInt(nodeid, key);
    }
    int padVal = max(1, 3 * floorLog2(heapSize + 1));
    odsPQ.Finalize(1, padVal);
    return minKey;
}
