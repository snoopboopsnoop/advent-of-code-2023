#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// first day this year where my solution feels very breakable

const int kCycles = 1000000000;

void rotateCounterClockwise(vector<string>& map);
void rotateClockwise(vector<string>& map);
int cycle(vector<string>& map);

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;
    int sum = 0;
    vector<string> map;
    vector<int> repeating;

    // read map into 2d vector
    while(in) {
        while(getline(in, line)) {
            if(line == "") break;
            
            map.push_back(line);
        }
    }

    for(const string& line : map) {
        cout << line << endl;
    }
    cout << endl;

    rotateCounterClockwise(map); // rotate so north is facing left

    bool foundRepeat = false; // if repeating section was found
    int iter = 1; // cycle tracker
    while(!foundRepeat) {
        int result = cycle(map);
        repeating.push_back(result);
        ++iter;

        auto repeat = find(repeating.begin(), repeating.end() - 1, result);

        // compare rest of range for repeat, cringe because you need it to repeat twice before it detects
        if(repeating.size() != 1 && repeat != repeating.end() - 1) {
            auto start = repeat;
            auto end = repeating.end() - 1;
            if(end - start == 1) continue; // if they're next to each other there's no shot they're a repeating group

            while(end != repeat) {
                --start;
                --end;
                if(*start != *end) break;
                else if(start == repeating.begin() && end != repeat) break;
            }
            // check if successful loop
            if(end == repeat) {
                foundRepeat = true;
                repeating.erase(end + 1, repeating.end());
                repeating.erase(repeating.begin(), start + 1);
            }
        }
    }

    int patternSize = repeating.size();
    int repeatPos = iter - 2 * patternSize; // cycle where the repeating group begins

    cout << "found repeating section of size " << patternSize << " starting on cycle " << repeatPos << ":" << endl;
    for(int i : repeating) {
        cout << i << ", ";
    }
    cout << endl;

    int mod = kCycles % patternSize; // mod cycle limit by group size

    while(mod < repeatPos) {
        mod += patternSize; // since everything before repeatPos isn't repeated, move mod to within group bounds
    }

    // solution is just the weight of the modulo'd cycle weight
    cout << endl << "Load on north support after 1 trillion cycles: " << repeating[mod - repeatPos] << endl;

    return 0;
}

// returns weight and alters map after a cycle
int cycle(vector<string>& map) {
    for(int j = 0; j < 4; ++j) {
        for(string& line : map) {
            int limit = -1; // can go all the way to edge of map initially
            // go through each rock in map and find end position
            for(int i = 0; i < line.size(); ++i) {
                char c = line[i];
                if(c == 'O') {
                    int cubePos = line.rfind('#', i); // check for cube rocks
                    if(cubePos > limit) limit = cubePos; // if cube rocks are closer than limit set it
                    line[i] = '.';  // remove rock from current pos
                    line[limit + 1] = 'O'; // move rock to stopping pos
                    limit = limit + 1; // new limit set to rock's stopping position
                }
            }
        }
        rotateClockwise(map); // this is slow but i don't want to write the logic for nsew
    }

    int weight = 0;
    // get weight of map
    for(int col = 0; col < map.size(); ++col) {
        const string line = map[col];
        for(int row = 0; row < line.size(); ++row) {
            if(line[row] == 'O') {
                weight += map.size() - row;
            }
        }
    }

    return weight;
}

// rotates 2d vector counter clockwise
void rotateCounterClockwise(vector<string>& map) {
    vector<string> temp(map[0].size());

    for(int i = 0; i < map.size(); ++i) {
        const string& line = map[i];
        for(int j = line.size() - 1; j >= 0; --j) {
            temp[line.size() - 1 - j].push_back(line[j]);
        }
    }

    map = temp;
}

// rotates 2d vector clockwise
void rotateClockwise(vector<string>& map) {
    vector<string> temp(map[0].size());

    for(int i = map.size() - 1; i >= 0; --i) {
        const string& line = map[i];
        for(int j = 0; j < line.size(); ++j) {
            temp[j].push_back(line[j]);
        }
    }

    map = temp;
}