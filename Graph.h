//
// Created by zconlin on 3/31/2023.
//

#ifndef CS236PROJECT5_RULEEVALUATION_GRAPH_H
#define CS236PROJECT5_RULEEVALUATION_GRAPH_H

#include "Node.h"

class Graph {

public:
    vector<int> postorderStack;
    map<int,Node> nodes;

    Graph(int size) {
        for (int nodeID = 0; nodeID < size; nodeID++)
            nodes[nodeID] = Node();
    }

    void addEdge(int fromNodeID, int toNodeID) {
        nodes[fromNodeID].addEdge(toNodeID);
    }

//    Graph dfs(int n, vector<int> order) {
//        Node &currentNode = nodes[n];
//        if (currentNode.visited) {
//            Graph result = Graph(0);
//            result.nodes.insert({n, currentNode});
//            return result;
//        } else {
//            currentNode.visited = true;
//        }
//        for (auto it = order.begin(); it != order.end(); it++) {
//            if (*it == n) {
//                order.erase(it);
//                break;
//            }
//        }
//        Graph combinedGraph = Graph(0);
//        for (const auto i: order) {
//            vector<Graph> subGraphs;
//            if (currentNode.getAdjacentNodeIDs().count(i)) {
//                Graph subGraph = dfs(i, order);
//                subGraphs.push_back(subGraph);
//            }
//            for (const auto &subGraph: subGraphs) {
//                for (const auto &node: subGraph.nodes) {
//                    combinedGraph.nodes.insert(node);
//                }
//            }
//            combinedGraph.nodes.insert({n, currentNode});
//        }
//        postorderStack.push_back(n);
//        combinedGraph.postorderStack = this->postorderStack;
//        return combinedGraph;
//    }

    // Run DFS-Forest on the reverse dependency graph to obtain post-order numbers.
    // Run DFS-Forest on the reverse dependency graph. Assign postorder numbers to each node visited in the search
    // starting with a postorder number of 1. When there is a choice of which node to visit next, choose the node
    // identifier that comes first numerically.
//    Graph dfsForest(vector<int> order) {
//
//    }

    string toString() {
        string output = "";
        for (auto node: nodes) {
            output += "R" + to_string(node.first) + ":" + node.second.toString();
        }
    return output;
    }
};

#endif //CS236PROJECT5_RULEEVALUATION_GRAPH_H
