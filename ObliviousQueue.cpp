#include "ObliviousQueue.h"
#include "Utilities.h"
#include <unordered_map>
#include <string>
using namespace std;

// Each queue node holds a payload and a pointer to the next node.
struct QueueNode {
    int id;
    string data;
    int nextId;  // 0 indicates null
};

static unordered_map<int, QueueNode> queueStorage;
static int queueHead = 0; // pointer used for insertion
static int queueTail = 0; // pointer used for removal

ObliviousQueue::ObliviousQueue() {
    queueHead = 0;
    queueTail = 0;
}

void ObliviousQueue::Enqueue(const string &data) {
    // ODS.Start()
    int id = nextid();
    QueueNode node;
    node.id = id;
    node.data = data;
    node.nextId = id;  // per pseudocode “pre-selection” trick
    queueStorage[id] = node;
    queueHead = id;
    if (queueTail == 0) queueTail = id;
    // ODS.Finalize(tail, padVal = 1)
}

string ObliviousQueue::Dequeue() {
    if (queueTail == 0) return ""; // empty queue
    // ODS.Start()
    QueueNode node = queueStorage[queueTail];
    queueStorage.erase(queueTail);
    queueTail = node.nextId;
    if (queueTail == 0) queueHead = 0;
    // ODS.Finalize(tail, padVal = 1)
    return node.data;
}
