#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <utility>
#include <algorithm>
#include <numeric>

using namespace std;

// who the hell would ever want to be a math major

// just took what i wrote for part 1 and put it in a function
int getSteps(string& start, const map<string, pair<string, string>>& map, const string& directions);

// euclidean algorthim for gcd ??
long long gcd(long long x, long long y) { 
    if(y == 0) return x;

    return gcd(y, x % y);
}

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;
    string directions;
    map<string, pair<string, string>> map; // maps node to pair(left, right)
    vector<string> nodes; // starting nodes

    // read directions and map
    while(in) {
        // directions
        getline(in, directions);
        getline(in, line);

        // map
        while(getline(in, line)) {
            if(line == "") break;
            
            string node = line.substr(0, line.find(' '));
            if(node.back() == 'A') nodes.push_back(node); // starting node
            string left = line.substr(line.find('(') + 1, line.find(',') - line.find('(') - 1);
            string right = line.substr(line.find(',') + 2);
            right.pop_back();

            map.insert(pair<string, pair<string, string>>(node, pair<string, string>(left, right)));
        }
    }

    vector<int> steps(nodes.size());
    
    // run 1 cycle for each starting node 
    for(int i = 0; i < nodes.size(); ++i) {
        steps[i] += getSteps(nodes[i], map, directions);
    }

    // solution is lcm of cycle lengths, for some reason
    long long sum = steps[0];
    for(int i = 1; i < steps.size(); ++i) {
        int step = steps[i];
        long long gcd_val = gcd(sum, step);
        sum = (sum * step) / gcd_val;
    }

    cout << sum << " steps until every version of you in spacetime is on a node that ends in \'Z\'" << endl;

    return 0;
}

int getSteps(string& start, const map<string, pair<string, string>>& map, const string& directions) {
    int sum = 0;
    auto iter = directions.begin();
    
    while(sum == 0 || start.back() != 'Z') {
        if(*iter == 'L') start = map.at(start).first;
        else start = map.at(start).second;
        ++sum;
        
        ++iter;
        if(iter == directions.end()) iter = directions.begin(); // loop iter back around
    }

    return sum;
}