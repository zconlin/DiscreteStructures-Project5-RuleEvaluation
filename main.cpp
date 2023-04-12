//
// Created by zconlin on 1/27/2023.
//

// "..\\tests\project5-passoff\20\input22.txt"

#include "scanner.h"
#include "token.h"
#include "parser.h"
#include "Scheme.h"
#include "Tuple.h"
#include "Relation.h"
#include "Interpreter.h"
#include "Node.h"
#include "Graph.h"
#include <iostream>
#include <fstream>

int main (int argc, char* argv[]) {
    ifstream f;
    f.open(argv[1]);

    string content((istreambuf_iterator<char>(f)), (istreambuf_iterator<char>()));

    Scanner s = Scanner(content);
    vector<Token> t = s.scanLoop();

    Parser p = Parser(t);

    try {

//         predicate names for fake rules
    // first is name for head predicate
    // second is names for body predicates
//    pair<string,vector<string>> ruleNames[] = {
//            { "A", { "B", "C" } },
//            { "B", { "A", "D" } },
//            { "B", { "B" } },
//            { "E", { "F", "G" } },
//            { "E", { "E", "F" } },
//    };

//        vector<Rule> rules;

        DatalogProgram dp = p.datalogProgram();
        Interpreter i = Interpreter(dp);


        i.evaluateAllRules();
        i.evaluateAllQueries();
    }
    catch (Token error) {
//        cout << "Failure!" << endl;
//        cout << "  " << error.toString() << endl;
    }
    return 0;
}


//int main() { // Hardcoded test
//    // predicate names for fake rules
//    // first is name for head predicate
//    // second is names for body predicates
//    pair<string,vector<string>> ruleNames[] = {
//            { "A", { "B", "C" } },
//            { "B", { "A", "D" } },
//            { "B", { "B" } },
//            { "E", { "F", "G" } },
//            { "E", { "E", "F" } },
//    };
//
//    vector<Rule> rules;
//
//    for (auto& rulePair : ruleNames) {
//        string headName = rulePair.first;
//        Rule rule = Rule(Predicate(headName));
//        vector<string> bodyNames = rulePair.second;
//        for (auto& bodyName : bodyNames)
//            rule.addBodyPredicate(Predicate(bodyName));
//        rules.push_back(rule);
//    }
//
//    pair<Graph,Graph> graphs = Interpreter::makeGraph(rules);
//    cout << "Dependency:" << endl << graphs.first.toString() << endl; // debug
//    cout << "Reverse Dependency:" << endl << graphs.second.toString() << endl; // debug
//    Graph dfsGraph = graphs.first.dfs(1, vector<int> { 0, 1, 2, 3, 4 });
//    cout << "DFS:" << endl << dfsGraph.toString() << endl; // debug
//    Graph reverseDfsGraph = graphs.second.dfs(1, vector<int> { 0, 1, 2, 3, 4 });
//    cout << "Reverse DFS:" << endl << reverseDfsGraph.toString() << endl; // debug
////    Graph postOrderGraph = graphs.first.dfsForest(1, vector<int> { 0, 1, 2, 3, 4 });
//
//}

//int main() { // Part 3
//
//    // predicate names for fake rules
//    // first is name for head predicate
//    // second is names for body predicates
//    pair<string,vector<string>> ruleNames[] = {
//            { "A", { "B", "C" } },
//            { "B", { "A", "D" } },
//            { "B", { "B" } },
//            { "E", { "F", "G" } },
//            { "E", { "E", "F" } },
//    };
//
//    vector<Rule> rules;
//
//    for (auto& rulePair : ruleNames) {
//        string headName = rulePair.first;
//        Rule rule = Rule(Predicate(headName));
//        vector<string> bodyNames = rulePair.second;
//        for (auto& bodyName : bodyNames)
//            rule.addBodyPredicate(Predicate(bodyName));
//        rules.push_back(rule);
//    }
//
//    Graph graph = Interpreter::makeGraph(rules);
//    cout << graph.toString();
//
//}

//int main() { // Part 2
//    Graph graph(3);
//    graph.addEdge(1,2);
//    graph.addEdge(1,0);
//    graph.addEdge(0,1);
//    graph.addEdge(1,1);
//    cout << graph.toString();
//}

//int main() { // Part 1
//    Node node;
//    node.addEdge(4);
//    node.addEdge(8);
//    node.addEdge(2);
//    cout << node.toString() << endl;
//}