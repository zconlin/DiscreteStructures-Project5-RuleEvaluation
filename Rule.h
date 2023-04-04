//
// Created by zconlin on 2/8/2023.
//

#ifndef CS236PROJECT2_DATALOGPARSER_RULE_H
#define CS236PROJECT2_DATALOGPARSER_RULE_H

#include "Predicate.h"

using namespace std;

class Rule
{
public:
    Rule() {}
    Rule(Predicate headPredicate)
            : headPredicate(headPredicate) {}
    Rule(Predicate headPredicate, vector<Predicate> predicateList)
            : headPredicate(headPredicate), predicateList(predicateList) {}

    Predicate headPredicate;
    vector<Predicate> predicateList;

    string toString() {
        stringstream output;
        if (predicateList.empty()) {
            return headPredicate.toString();
        }
//        Predicate savedParameter = predicateList.back();
//        predicateList.pop_back();
        output << headPredicate.toString() << " :- ";
        int counter = 0;
        for(auto i : predicateList) {
            if (counter != predicateList.size() - 1) {
                output << i.toString() + ",";
                ++counter;
            } else {
                output << i.toString();
            }
        }
//        output << savedParameter.toString();

        return output.str();
    }

    Rule addBodyPredicate(Predicate predicate) {
        predicateList.push_back(predicate);
        return *this;
    }

    Predicate getBodyPredicate(unsigned int i) {
        return predicateList.at(i);
    }

    unsigned int getSize() {
        return predicateList.size();
    }

    Predicate getHeadPredicate() {
        return headPredicate;
    }

private:
    string value;
};

#endif //CS236PROJECT2_DATALOGPARSER_RULE_H
