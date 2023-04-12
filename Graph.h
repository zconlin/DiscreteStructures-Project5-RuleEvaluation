//
// Created by zconlin on 3/31/2023.
//

#ifndef CS236PROJECT5_RULEEVALUATION_GRAPH_H
#define CS236PROJECT5_RULEEVALUATION_GRAPH_H

#include "Node.h"
#include <algorithm>

class Graph {

public:
    vector<int> postOrderStack;
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
//        postOrderStack.push_back(n);
//        combinedGraph.postOrderStack = this->postOrderStack;
//        return combinedGraph;
//    }

    Graph DFS(int n, vector<int> order) {
        Node &currentNode = nodes.at(n);
        if (currentNode.visited) {
            return Graph(0);
        } else {
            currentNode.visited = true;
        }

        for (auto it = order.begin(); it != order.end(); it++) {
            if (*it == n) {
                order.erase(it);
                break;
            }
        }

        Graph combinedGraph = Graph(0);
        for (const auto i : order) {
            vector<Graph> subgraphs;
            if (currentNode.adjacentNodeIDs.count(i)) {
                Graph subgraph = DFS(i, order);
                subgraphs.push_back(subgraph);
            }

            for (const auto& subgraph : subgraphs) {
                for (const auto &node: subgraph.nodes) {
                    combinedGraph.nodes.insert(node);
                }
            }
        }
        combinedGraph.nodes.insert({n, currentNode});

        postOrderStack.push_back(n);
        combinedGraph.postOrderStack = this->postOrderStack;
        return combinedGraph;
    }

    vector<Graph> DFSforest(vector<int> order) {
        vector<Graph> components;
        int c = 0;
        while (!order.empty()) {
            int start = order.front();
            order.erase(order.begin());
            Graph component = DFS(start, order);
            components.push_back(component);
            for (auto it = order.begin(); it != order.end(); it++) {
                if (component.nodes.count(*it)) {
                    order.erase(it);
                    it--;
                }
            }
            c = c + 1;
        }

        return components;
    }

    vector<int> getPostOrder() {
        vector<int> order;
        for (unsigned int i = 0; i < nodes.size(); i++) {
            order.push_back(int(i));
        }

        vector<Graph> components = DFSforest(order);

        return components.back().postOrderStack;
    }

    string nodesToString() {
        stringstream out;
        for (const auto& pair: nodes) {
            int nodeID = pair.first;
            Node node = pair.second;

            if (nodeID != nodes.rbegin()->first) {
                out << "R" << nodeID << ",";
            } else {
                out << "R" << nodeID;
            }
        }

        return out.str();
    }

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
