#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// struct for easier access than tuple
struct Rule {
    unsigned long first = 0;
    unsigned long last = 0;
    unsigned long op = 0;

    Rule(unsigned long first, unsigned long last, unsigned long op) {
        this->first = first;
        this->last = last;
        this->op = op;
    }
};

// holds a set of rules that can be applied to a range of numbers
struct Map {
    // purely for display (that isn't even used anymore)
    string fromName;
    string toName;
    vector<Rule> mappings; // holds all map information for one rule

    Map(const string& from, const string& to) {
        fromName = from;
        toName = to;
    }

    void add(const Rule& rule) {
        mappings.push_back(rule);

        sort(mappings.begin(), mappings.end(), [](const Rule& a, const Rule& b) {
            return a.first < b.first;
        });
    } 

    // processes everything in param vector and transforms them by this mapping
    void applyRules(vector<pair<unsigned long, unsigned long>>& ranges) const {
        int size = ranges.size();
        int offset = 0;
        for(int i = 0; i < size; ++i) {
            pair<unsigned long, unsigned long> range = ranges[i - offset];
            int complete = 0; // -1 = not fully processed, 0 = no applicable transforms, 1 = fully processed
            while(!complete || complete == -1) {
                complete = 0;
                // look through all rules for overlapping ranges
                for(const Rule& rule : mappings) {
                    // first of range is encompassed in rule
                    if(range.first >= rule.first && range.first <= rule.last) {
                        // end of range is encompased in rule
                        if(range.second <= rule.last) {
                            ranges.push_back(pair<unsigned long, unsigned long>(range.first + rule.op, range.second + rule.op));
                            complete = 1;
                            break;
                        }
                        // end of range is outside of rule, need to continue processing
                        else {
                            ranges.push_back(pair<unsigned long, unsigned long>(range.first + rule.op, rule.last + rule.op));
                            range.first = rule.last+1;
                            complete = -1;
                            break;
                        }
                    }
                    // first of range outside of rule but some other part is inside rule
                    else if(range.first < rule.first && range.second >= rule.first) {
                        ranges.push_back(pair<unsigned long, unsigned long>(range.first, rule.first-1));
                        range.first = rule.first;
                        complete = -1;
                        break;
                    }
                }
                // no part of range is in rule
                if(complete == 0) {
                    ranges.push_back(range);
                    complete = 1;
                }
            }
            ranges.erase(ranges.begin());
            offset++;
        }
    }
};

// printing a map, useless now
ostream &operator<<(ostream& os, const Map& map) {
    os << map.fromName << "-to-" << map.toName << " map:" << endl;
    return os;
}