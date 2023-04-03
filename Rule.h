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
        Predicate savedParameter = predicateList.back();
        predicateList.pop_back();
        output << headPredicate.toString() << " :- ";
        for(auto i : predicateList) {
            output << i.toString() + ",";
        }
        output << savedParameter.toString();

        return output.str();
    }

    Rule addBodyPredicate(Predicate predicate) {
        predicateList.push_back(predicate);
        return *this;
    }

    Rule getBodyPredicate() {
        return *this;
    }


private:
    string value;
};

#endif //CS236PROJECT2_DATALOGPARSER_RULE_H
