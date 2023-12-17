#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// first day this year where my solution feels very breakable

void rotate(vector<string>& map);

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;
    int sum = 0;
    vector<string> map;

    // read map into 2d vector
    while(in) {
        while(getline(in, line)) {
            if(line == "") break;
            map.push_back(line);
        }
    }

    rotate(map); // rotated the map cuz processing easier but program slower but who cares

    for(string line : map) {
        cout << line << endl;
    }

    for(string line : map) {
        int limit = -1; // can go all the way to edge of map initially
        // go through each rock in map and find end position
        for(int i = 0; i < line.size(); ++i) {
            char c = line[i];
            if(c == 'O') {
                int cubePos = line.rfind('#', i); // check for cube rocks
                if(cubePos > limit) limit = cubePos; // if cube rocks are closer than limit set it
                int stop = limit + 1; // stops one index before limit
                limit = stop; // new limit set to rock's stopping position
                sum += line.size() - stop; // add weight of rock to sum
            }
        }
    }

    cout << endl << "<-- north" << endl;

    cout << endl << "Sum of calibration values: " << sum << endl;

    return 0;
}

// rotates 2d vector 90 degrees counter clockwise
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