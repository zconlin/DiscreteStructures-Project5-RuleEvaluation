//
// Created by zconlin on 3/31/2023.
//

#ifndef CS236PROJECT5_RULEEVALUATION_NODE_H
#define CS236PROJECT5_RULEEVALUATION_NODE_H

using namespace std;
#include <set>
#include <iostream>
#include <stack>

class Node {

private:

    set<int> adjacentNodeIDs;

public:
    bool visited = false;
    int postorder;
    stack<int> postorderStack;

    void addEdge(int adjacentNodeID) {
        adjacentNodeIDs.insert(adjacentNodeID);
    }

    string toString() {
        string output = "";
        for (int i : adjacentNodeIDs) {
        output += "R" + to_string(i) + ",";
        }
        output = output.substr(0, output.size() - 1);
        output += "\n";

        return output;
    }

    set<int> getAdjacentNodeIDs() {
        return adjacentNodeIDs;
    }
};

#endif //CS236PROJECT5_RULEEVALUATION_NODE_H
