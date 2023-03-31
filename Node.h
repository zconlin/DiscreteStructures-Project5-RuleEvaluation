//
// Created by zconlin on 3/31/2023.
//

#ifndef CS236PROJECT5_RULEEVALUATION_NODE_H
#define CS236PROJECT5_RULEEVALUATION_NODE_H

using namespace std;
#include <set>
#include <iostream>

class Node {

private:

    set<int> adjacentNodeIDs;

public:

    void addEdge(int adjacentNodeID) {
    adjacentNodeIDs.insert(adjacentNodeID);
    }

    string toString() {
        string output = "";
        for (int i : adjacentNodeIDs) {
        output += "R" + to_string(i) + ",";
        }
        return output;
    }
};

#endif //CS236PROJECT5_RULEEVALUATION_NODE_H
