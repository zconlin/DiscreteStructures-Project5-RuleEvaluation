//
// Created by zconlin on 3/10/2023.
//

#ifndef CS236PROJECT4_DATALOGINTERPRETER_INTERPRETER_H
#define CS236PROJECT4_DATALOGINTERPRETER_INTERPRETER_H

#include "Database.h"
#include "parser.h"
#include "Predicate.h"
#include "Graph.h"

class Interpreter {
public:
    Interpreter(){}

    Interpreter(const DatalogProgram &program) : dl(program) {
        db = Database(program.Schemes, program.Facts);
    }
    ~Interpreter(){}

    DatalogProgram dl;
    Database db;

    Relation evaluateQuery(Predicate &predicate) {
        Relation rel = db.relations[predicate.getName()];
        map<string, int> mapping;
        vector<string> ordering;
        Relation result = Relation(rel);
        int index = 0;
        for (auto &p: predicate.parameterList) {
            if (!p.isID) {
                result = result.select(index, p.value);
            } else {
                if (mapping.count(p.value)) {
                    int baselineIndex = mapping[p.value];
                    result = result.matchSelect(baselineIndex, index);
                } else {
                    ordering.push_back(p.value);
                    mapping[p.value] = index;
                }
            }
            ++index;
        }
        cout << predicate.toString() << "? ";

        if (result.getTuples().empty()) {
            cout << "No" << endl;
        } else {
            if (!ordering.empty()) {
                Scheme returnScheme = Scheme();
                for (auto &item: ordering) {
                    returnScheme.push_back(rel.scheme.at(mapping[item]));
                }
                result = result.project(returnScheme);
                result = result.rename(Scheme(ordering));
//                result = result.join();
                cout << "Yes(" << result.getTuples().size() << ")" << endl;
                cout << result.toString();
            } else {
                cout << "Yes(" << result.getTuples().size() << ")" << endl;
            }
        }
        return result;
    }

    void evaluateAllQueries() {
        cout << "Query Evaluation" << endl;

        for (auto &query : dl.Queries) {
            evaluateQuery(query);
        }
    }

    Relation evaluateRule(Predicate &predicate) {
        Relation rel = db.relations[predicate.getName()];
        map<string, int> mapping;
        vector<string> ordering;
        Relation result = Relation(rel);
        int index = 0;
        for (auto &p: predicate.parameterList) {
            if (!p.isID) {
                result = result.select(index, p.value);
            } else {
                if (mapping.count(p.value)) {
                    int baselineIndex = mapping[p.value];
                    result = result.matchSelect(baselineIndex, index);
                } else {
                    ordering.push_back(p.value);
                    mapping[p.value] = index;
                }
            }
            ++index;
        }
        cout << predicate.toString() << "? ";

        if (result.getTuples().empty()) {
            cout << "No" << endl;
        } else {
            if (!ordering.empty()) {
                Scheme returnScheme = Scheme();
                for (auto &item: ordering) {
                    returnScheme.push_back(rel.scheme.at(mapping[item]));
                }
                result = result.project(returnScheme);
                result = result.rename(Scheme(ordering));
                cout << "Yes(" << result.getTuples().size() << ")" << endl;
                cout << result.toString();
            } else {
                cout << "Yes(" << result.getTuples().size() << ")" << endl;
            }
        }
        return result;
    }

    void evaluateAllRules() {
        int numPasses = 0;

        cout << "Dependency Graph" << endl;
        pair<Graph,Graph> graphs = makeGraph(dl.Rules);
        Graph graph = graphs.first;
        Graph reverseGraph = graphs.second;

        cout << endl; // debug
        cout << "Rule Evaluation" << endl;

        for (auto &fact : dl.Facts) {
            ++numPasses;
            evaluateRule(fact);
        }

        vector<int> order;
        for (int i = 0; i < graph.nodes.size(); i++) {
            order.push_back(i);
        }
        cout << endl; // debug
//        cout << endl << "Schemes populated after " << numPasses
//        << " passes through the Rules." << endl << endl;
    }

     static pair<Graph,Graph> makeGraph(const vector<Rule>& rules) {
        Graph graph(rules.size());
        Graph reverseGraph(rules.size());
        for (unsigned fromID = 0; fromID < rules.size(); fromID++) {
            Rule fromRule = rules.at(fromID);
            // cout << "from rule R" << fromID << ": " << fromRule.toString() << endl; // debug

            for (unsigned pred = 0; pred < fromRule.getSize(); pred++) {
                Predicate bodyPred = fromRule.getBodyPredicate(pred);
                // cout << "from body predicate: " << bodyPred.toString() << endl; // debug

                for (unsigned toID = 0; toID < rules.size(); toID++) {
                    Rule toRule = rules.at(toID);
                    // cout << "to rule R" << toID << ": " << toRule.toString() << endl; // debug
                    if (toRule.getHeadPredicate().getName() == bodyPred.getName()) {
                        graph.addEdge(fromID, toID);
                        reverseGraph.addEdge(toID, fromID);
                        // cout << "dependency found: (R" << fromID << ",R" << toID << ")" << endl; // debug
                    }
                }
            }
        }
        // cout << endl; // debug
        return {graph, reverseGraph};
    }

    Relation evaluateSCC(const vector<Rule> &rules) {
        return Relation();
    }
};

#endif //CS236PROJECT4_DATALOGINTERPRETER_INTERPRETER_H
