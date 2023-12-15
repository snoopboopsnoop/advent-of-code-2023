#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// uh oh i haven't programmed in c++ since may

void rotate(vector<string>& map);

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;
    int sum = 0;
    vector<string> map;
    vector<pair<int, int>> rocks; // coords of rocks

    // read sum of calibration document values
    while(in) {
        while(getline(in, line)) {
            if(line == "") break;
            
            map.push_back(line);
        }
    }

    rotate(map);

    cout << "<-- north" << endl;

    for(string line : map) {
        cout << line << endl;
    }

    for(string line : map) {
        cout << "looking at " << line << endl;
        int limit = -1;
        for(int i = 0; i < line.size(); ++i) {
            char c = line[i];
            if(c == 'O') {
                int cubePos = line.rfind('#', i);
                if(cubePos > limit) limit = cubePos;
                int stop = limit + 1;
                cout << "rock at pos " << i << " stops at " << stop << " with load of " << line.size() - stop << endl;
                limit = stop;
                sum += line.size() - stop;
            }
        }
    }


    cout << "Sum of calibration values: " << sum << endl;

    return 0;
}

void rotate(vector<string>& map) {
    vector<string> temp(map[0].size());

    for(int i = 0; i < map.size(); ++i) {
        string line = map[i];
        for(int j = line.size() - 1; j >= 0; --j) {
            temp[line.size() - 1 - j].push_back(line[j]);
        }
    }

    map = temp;
}