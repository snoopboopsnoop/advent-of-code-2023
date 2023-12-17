#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// uh oh i haven't programmed in c++ since may

struct Lens{
    int focalLength;
    string label;

    Lens(int len, string name) : focalLength(len), label(name) {}
};

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;
    int sum = 0;
    map<int, vector<Lens>> map;
    
    // read sum of calibration document values
    getline(in, line);

    istringstream sin(line);

    string token;
    while(getline(sin, token, ',')) {

        int hash = 0;
        int len = -1;
        for(char c : token) {
            if(c == '=') {
                len = token.back() - '0';
                break;
            }
            else if(c == '-') break;
            hash += c;
            hash *= 17;
            hash = hash % 256;
        }
        cout << token << ": " << hash << endl;

        if(len != -1) {
            if(map.find(hash) == map.end()) {
                map[hash] = vector<Lens>();
            }

            string label = token.substr(0, token.find('='));
            auto found = find_if(map[hash].begin(), map[hash].end(), [ label ] (Lens a) { return a.label == label; });

            if(found != map[hash].end()) {
                found->focalLength = len;
            }
            else map[hash].push_back(Lens(len, label));
        }
        else {
            string label = token.substr(0, token.find('-'));
            if(map.find(hash) != map.end()) {
                auto found = find_if(map[hash].begin(), map[hash].end(), [ label ](Lens a) { return a.label == label; });
                if(found != map[hash].end()) {
                    map[hash].erase(found);
                }
            }
        }
    }

    for(auto pair : map) {
        cout << "box" << pair.first << ": " << endl;
        for(int i = 0; i < pair.second.size(); ++i) {
            Lens lens = pair.second[i];
            cout << "[" << lens.label << " " << lens.focalLength << "] ";
            sum += (pair.first + 1) * (i + 1) * lens.focalLength;
        }
        cout << endl;
    }

    cout << "Sum of calibration values: " << sum << endl;

    return 0;
}