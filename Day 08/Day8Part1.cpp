#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <utility>

using namespace std;

// who the hell would ever want to be a math major

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;
    int sum = 0;
    string directions;
    map<string, pair<string, string>> map; // maps node to pair(left, right)

    // read directions and map
    while(in) {
        // directions
        getline(in, directions);
        getline(in, line);

        // map
        while(getline(in, line)) {
            if(line == "") break;
            
            string node = line.substr(0, line.find(' '));
            string left = line.substr(line.find('(') + 1, line.find(',') - line.find('(') - 1);
            string right = line.substr(line.find(',') + 2);
            right.pop_back();

            map.insert(pair<string, pair<string, string>>(node, pair<string, string>(left, right)));
        }
    }

    // start at AAA and first direction char
    string node = "AAA";
    auto iter = directions.begin();
    
    while(node != "ZZZ") {
        if(*iter == 'L') node = map.at(node).first;
        else node = map.at(node).second;
        ++sum;
        
        ++iter;
        if(iter == directions.end()) iter = directions.begin(); // loop iter back around
    }

    cout << sum << " steps to node ZZZ" << endl;

    return 0;
}