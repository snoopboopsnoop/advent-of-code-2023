#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

#include "Map.cpp"

using namespace std;

// dumb ass day 5 biggest difficulty spike ever

unsigned long algorithm(const pair<unsigned long, unsigned long>& seed, const vector<Map>& mapping);

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;
    unsigned long lowest = 0;
    
    // vector of starting seed # and its range
    vector<pair<unsigned long, unsigned long>> seeds;
    vector<Map> rules;
    
    // get list of seed numbers and ranges (first line)
    getline(in, line);
    line = line.substr(line.find(':') + 2);
    istringstream seedIn(line);

    // parse each pair into seeds vector
    while(seedIn.peek() != -1) {
        unsigned long seed = 0, range = 0;
        seedIn >> seed >> range;
        seeds.push_back(pair<unsigned long, unsigned long>(seed, range));
    }

    // get rid of extra space line
    getline(in, line);

    // read map title to line string
    while(getline(in, line)) {
        string from = line.substr(0, line.find('-'));
        string to = line.substr(line.find('-') + 4, line.find(' ') - (line.find('-') + 4));

        rules.push_back(Map(from, to));
        Map& currMap = rules.back();
        
        // read each mapping rule
        while(getline(in, line)) {
            // check for end of map
            if(line == "") break;
            
            // read values and write to map
            istringstream itemIn(line);
            unsigned long dest = 0, source = 0, range = 0;
            
            itemIn >> dest >> source >> range;
            currMap.add(Rule(source, source + range - 1, dest - source));
        }
    }

    for(const auto& seed : seeds) {
        cout << "smallest from " << seed.first << " -> " << seed.second+seed.first << ": ";
        unsigned long temp = algorithm(seed, rules);
        if(temp < lowest || lowest == 0) {
            lowest = temp;
            cout << "(new best) ";
        }
        cout << temp << endl;
    }

    cout << endl << "Lowest location number: " << lowest << endl;
    
    return 0;
}

// returns smallest location number after seed range (param) is sent through all maps 
unsigned long algorithm(const pair<unsigned long, unsigned long>& seed, const vector<Map>& mapping) {
    vector<pair<unsigned long, unsigned long>> ranges = { pair<unsigned long, unsigned long>(seed.first, seed.first + seed.second - 1) };
   
    for(const Map& map : mapping) {
        map.applyRules(ranges);
    }

    return (*min_element(ranges.begin(), ranges.end(), [](const auto& a, const auto& b) {
        return a.first < b.first;
    })).first;
}