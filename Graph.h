//
// Created by zconlin on 3/31/2023.
//

#ifndef CS236PROJECT5_RULEEVALUATION_GRAPH_H
#define CS236PROJECT5_RULEEVALUATION_GRAPH_H

#include "Node.h"

class Graph {

private:

    map<int,Node> nodes;

public:

    Graph(int size) {
        for (int nodeID = 0; nodeID < size; nodeID++)
            nodes[nodeID] = Node();
    }

    void addEdge(int fromNodeID, int toNodeID) {
        nodes[fromNodeID].addEdge(toNodeID);
    }

    string toString() {
        string output = "";
        for (auto node: nodes) {
            output += "R" + to_string(node.first) + ": " + node.second.toString();
        }
    return output;
    }
};

#endif //CS236PROJECT5_RULEEVALUATION_GRAPH_H
