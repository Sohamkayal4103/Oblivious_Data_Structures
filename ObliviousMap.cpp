#include "ObliviousMap.h"
#include "ODSClient.h"
#include "Utilities.h"
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

static ODSClientObj<MapNode> odsMap;

ObliviousMap::ObliviousMap() : root(0) { }

int maxVal(int a, int b) {
    return (a > b) ? a : b;
}

int nodeHeight(const MapNode &node) {
    return maxVal(node.ht1, node.ht2) + 1;
}

pair<int,int> ObliviousMap::RotLC(int id) {
    MapNode A = odsMap.AccessRead(id);
    MapNode B = odsMap.AccessRead(A.left);
    int oldBRight = B.right;
    A.ht1 = B.ht2;
    A.left = oldBRight;
    odsMap.AccessWrite(id, A);
    int newH = maxVal(B.ht2, A.ht2) + 1;
    B.right = id;
    B.ht2 = newH;
    odsMap.AccessWrite(B.id, B);
    int newH_B = maxVal(B.ht1, B.ht2) + 1;
    return {B.id, newH_B};
}

pair<int,int> ObliviousMap::RotRC(int id) {
    MapNode A = odsMap.AccessRead(id);
    MapNode B = odsMap.AccessRead(A.right);
    int oldBLeft = B.left;
    A.ht2 = B.ht1;
    A.right = oldBLeft;
    odsMap.AccessWrite(id, A);
    int newH = maxVal(A.ht1, B.ht1) + 1;
    B.left = id;
    B.ht1 = newH;
    odsMap.AccessWrite(B.id, B);
    int newH_B = maxVal(B.ht1, B.ht2) + 1;
    return {B.id, newH_B};
}

pair<int,int> ObliviousMap::DbRotLC(int id) {
    MapNode A = odsMap.AccessRead(id);
    pair<int,int> p = RotRC(A.left);
    A.left = p.first;
    odsMap.AccessWrite(id, A);
    return RotLC(id);
}

pair<int,int> ObliviousMap::DbRotRC(int id) {
    MapNode A = odsMap.AccessRead(id);
    pair<int,int> p = RotLC(A.right);
    A.right = p.first;
    odsMap.AccessWrite(id, A);
    return RotRC(id);
}

pair<int,int> ObliviousMap::Balance(int id) {
    MapNode node = odsMap.AccessRead(id);
    if (node.ht1 - node.ht2 > 1) {
        MapNode L = odsMap.AccessRead(node.left);
        if (L.ht1 >= L.ht2)
            return RotLC(id);
        else
            return DbRotLC(id);
    } else if (node.ht2 - node.ht1 > 1) {
        MapNode R = odsMap.AccessRead(node.right);
        if (R.ht1 >= R.ht2)
            return RotRC(id);
        else
            return DbRotRC(id);
    }
    return {id, nodeHeight(node)};
}

MapNode ObliviousMap::FindPriv(int key, int nodeid) {
    if (nodeid == 0) {
        MapNode dummy;
        dummy.id = 0;
        return dummy;
    }
    MapNode node = odsMap.AccessRead(nodeid);
    if (key == node.key)
        return node;
    else if (key < node.key)
        return FindPriv(key, node.left);
    else
        return FindPriv(key, node.right);
}

int ObliviousMap::InsertPriv(int key, int nodeid) {
    if (nodeid == 0) {
        int id = nextid();
        MapNode newNode;
        newNode.id = id;
        newNode.key = key;
        newNode.ht1 = 0;
        newNode.ht2 = 0;
        newNode.left = 0;
        newNode.right = 0;
        odsMap.AccessInsert(id, newNode);
        return id;
    }
    MapNode node = odsMap.AccessRead(nodeid);
    if (key < node.key) {
        node.left = InsertPriv(key, node.left);
    } else if (key > node.key) {
        node.right = InsertPriv(key, node.right);
    } else {
        odsMap.AccessWrite(nodeid, node);
        return nodeid;
    }
    odsMap.AccessWrite(nodeid, node);
    pair<int,int> balanced = Balance(nodeid);
    return balanced.first;
}

void ObliviousMap::Insert(int key) {
    odsMap.Start();
    root = InsertPriv(key, root);
    int padVal = static_cast<int>(ceil(1.44 * 3 * log2(max(1, root))));
    odsMap.Finalize(root, padVal);
}

MapNode ObliviousMap::Find(int key) {
    odsMap.Start();
    MapNode res = FindPriv(key, root);
    int padVal = static_cast<int>(ceil(1.44 * 3 * log2(max(1, root))));
    odsMap.Finalize(root, padVal);
    return res;
}

void ObliviousMap::InOrder(int nodeid) {
    if (nodeid == 0) return;
    MapNode node = odsMap.AccessRead(nodeid);
    InOrder(node.left);
    cout << node.key << " ";
    InOrder(node.right);
}

void ObliviousMap::PrintInOrder() {
    InOrder(root);
    cout << endl;
}
