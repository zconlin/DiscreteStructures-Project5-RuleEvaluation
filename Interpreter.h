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

//    void evaluateAllRules() {
//        cout << "Dependency Graph" << endl;
//        pair<Graph,Graph> graphs = makeGraph(dl.Rules());
//        Graph forwardGraph = graphs.first;
//        cout << forwardGraph.toString() << endl;
//        Graph reverseGraph = graphs.second;
//        cout << "reverse graph" << endl << reverseGraph.toString() << endl; //debug
//
//        cout << "Rule Evaluation" << endl;
//        vector<int> order = reverseGraph.getPostOrder();
//        std::reverse(order.begin(), order.end());
//        vector<Graph> SCCs = forwardGraph.DFSforest(order);
//
//        for (const auto &SCC: SCCs) {
//            int ruleNum = SCC.nodes.begin()->first;
//            cout << "SCC: R" << ruleNum << endl;
//
//            vector<Rule> rules;
//            for (const auto &[i, node]: SCC.nodes) {
//                rules.push_back(dl.Rules().at(i));
//            }
//
//            bool changed = true;
//            int iteration = 0;
//
//            if (rules.size() == 1) {
//                Rule &rule = rules.at(0);
//                // Check if rule doesn't depend on itself
//                bool dependent = false;
//                for (const auto &p: rule.body) {
//                    if (p.name == rule.headPredicate.name) {
//                        dependent = true;
//                        changed = true;
//                        break;
//                    }
//                }
//                if (!dependent) {
//                    cout << rule.toString() << endl;
//                    Relation result = evaluateRule(rule);
//                    cout << result.toString();
//
//                    changed = false;
//                    iteration = 1;
//                }
//            }
//
//            while (changed) {
//                changed = false;
//                for (const auto &rule: rules) {
//                    unsigned int before = db.relations[rule.headPredicate.name].getTuples().size();
//                    cout << rule.toString() << endl;
//                    Relation result = evaluateRule(rule);
//                    cout << result.toString();
//                    if (before != db.relations[rule.headPredicate.name].getTuples().size()) {
//                        changed = true;
//                    }
//                }
//                ++iteration;
//            }
//            cout << iteration << " passes: R" << ruleNum << endl;
////        cout << endl << "Schemes populated after " << iteration << " passes through the Rules." << endl << endl;
//
//        }
//    }

    void evaluateAllRules() {

        cout << "Dependency Graph" << endl;

        if (dl.Rules.empty()) {
            cout << endl << "Rule Evaluation" << endl;
            // No rules to evaluate
            return;
        }

        pair<Graph,Graph> graphs = makeGraph(dl.Rules);
        Graph forwardGraph = graphs.first;
        cout << forwardGraph.toString() << endl;
        Graph reverseGraph = graphs.second;

        cout << "Rule Evaluation" << endl;
        vector<int> order = reverseGraph.getPostOrder();
        std::reverse(order.begin(), order.end());
        vector<Graph> SCCs = forwardGraph.DFSforest(order);

        for(auto& SCC : SCCs) {
            string ruleNum = SCC.nodesToString();
            cout << "SCC: " << ruleNum << endl;

            vector<Rule> rules;
            for (const auto& [i, node] : SCC.nodes) {
                rules.push_back(dl.Rules.at(i));
            }

            bool changed = true;
            int iteration = 0;

            if (rules.size() == 1) {
                Rule& rule = rules.at(0);
                bool dependent = false;
                for (const auto& p : rule.predicateList) {
                    if (p.name == rule.headPredicate.name) {
                        dependent = true;
                        changed = true;
                        break;
                    }
                }
                if (!dependent) {
                    cout << rule.toString() << endl;
                    Relation result = evaluateRule(rule);
                    cout << result.toString();

                    changed = false;
                    iteration = 1;
                }
            }

            while (changed) {
                changed = false;
                for (const auto& rule : rules) {
                    unsigned int before = db.relations[rule.headPredicate.name].getTuples().size();
                    cout << rule.toString() << endl;
                    Relation result = evaluateRule(rule);
                    cout << result.toString();
                    if (before != db.relations[rule.headPredicate.name].getTuples().size()) {
                        changed = true;
                    }
                }
                ++iteration;
            }
            cout << iteration << " passes: " << ruleNum << endl;
//        cout << endl << "Schemes populated after " << iteration << " passes through the Rules." << endl << endl;

        }
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
