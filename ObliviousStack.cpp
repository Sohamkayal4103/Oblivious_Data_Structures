#include "ObliviousStack.h"
#include "Utilities.h"
#include <unordered_map>
#include <string>
using namespace std;

// Each stack node holds a payload and a pointer (nextId)
struct StackNode {
    int id;
    string data;
    int nextId;  // 0 indicates null
};

// For demonstration, we use a static storage (in practice, this would be via ODS/ORAM)
static unordered_map<int, StackNode> stackStorage;
static int stackTop = 0;

ObliviousStack::ObliviousStack() { 
    stackTop = 0;
}

void ObliviousStack::Push(const string &data) {
    // ODS.Start() would be called here
    int id = nextid();
    StackNode node;
    node.id = id;
    node.data = data;
    node.nextId = stackTop;  // new node points to previous top
    stackStorage[id] = node;
    stackTop = id;
    // ODS.Finalize(top, padVal = 1)
}

string ObliviousStack::Pop() {
    if (stackTop == 0) return ""; // empty stack
    // ODS.Start()
    StackNode node = stackStorage[stackTop];
    stackStorage.erase(stackTop);
    stackTop = node.nextId;
    // ODS.Finalize(top, padVal = 1)
    return node.data;
}
