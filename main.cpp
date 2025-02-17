#include <iostream>
#include "ObliviousStack.h"
#include "ObliviousQueue.h"
#include "ObliviousPriorityQueue.h"
#include "ObliviousMap.h"
using namespace std;

int main() {
    cout << "Oblivious Stack Demo:" << endl;
    ObliviousStack stack;
    stack.Push("Alice");
    stack.Push("Bob");
    cout << "Pop: " << stack.Pop() << endl;   // Expect "Bob"
    cout << "Pop: " << stack.Pop() << endl;   // Expect "Alice"
    cout << "Pop (empty): " << stack.Pop() << endl;
    
    cout << "\nOblivious Queue Demo:" << endl;
    ObliviousQueue queue;
    queue.Enqueue("X");
    queue.Enqueue("Y");
    cout << "Dequeue: " << queue.Dequeue() << endl; // Expect "X"
    cout << "Dequeue: " << queue.Dequeue() << endl; // Expect "Y"
    cout << "Dequeue (empty): " << queue.Dequeue() << endl;
    
    cout << "\nOblivious Priority Queue Demo:" << endl;
    ObliviousPriorityQueue pq;
    pq.Insert(5);
    pq.Insert(2);
    pq.Insert(9);
    pq.Insert(1);
    cout << "ExtractMin: " << pq.ExtractMin() << endl;
    cout << "ExtractMin: " << pq.ExtractMin() << endl;
    
    cout << "\nOblivious Map (AVL Tree) Demo:" << endl;
    ObliviousMap omap;
    omap.Insert(50);
    omap.Insert(30);
    omap.Insert(70);
    omap.Insert(20);
    omap.Insert(40);
    omap.Insert(60);
    omap.Insert(80);
    cout << "In-Order Traversal of AVL Map: ";
    omap.PrintInOrder();
    auto found = omap.Find(40);
    if(found.id != 0)
        cout << "Found key: " << found.key << endl;
    else
        cout << "Key 40 not found." << endl;
    
    return 0;
}
