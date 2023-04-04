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

    // call this after schemes and facts, but before queries
    void evaluateAllQueries() {
        for (auto &query : dl.Queries) {
            evaluateQuery(query);
        }
    }

    Relation evaluateFact(Predicate &predicate) {
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

    void evaluateAllFacts() {
        int numPasses = 0;
        int sizeBefore = 0;
        int sizeAfter = 0;

        for (auto &fact : dl.Facts) {
            ++numPasses;
            evaluateFact(fact);
        }
        
        cout << endl << "Schemes populated after " << numPasses
        << " passes through the Rules." << endl << endl;
    }

    static Graph makeGraph(const vector<Rule>& rules) {
        Graph graph(rules.size());
        for (unsigned fromID = 0; fromID < rules.size(); fromID++) {
            Rule fromRule = rules.at(fromID);
//            cout << "from rule R" << fromID << ": " << fromRule.toString() << endl; // debug
            for (unsigned pred = 0; pred < fromRule.getSize(); pred++) {
                Predicate bodyPred = fromRule.getBodyPredicate(pred);
//                cout << "from body predicate: " << bodyPred.toString() << endl; // debug
                for (unsigned toID = 0; toID < rules.size(); toID++) {
                    Rule toRule = rules.at(toID);
//                    cout << "to rule R" << toID << ": " << toRule.toString() << endl; // debug
                    if (toRule.getHeadPredicate().getName() == bodyPred.getName()) {
//                        cout << "dependency found: (R" << fromID << ",R" << toID << ")" << endl; // debug
                        graph.addEdge(fromID, toID);
                    }
                }
            }

        }

        return graph;
    }
};

#endif //CS236PROJECT4_DATALOGINTERPRETER_INTERPRETER_H
