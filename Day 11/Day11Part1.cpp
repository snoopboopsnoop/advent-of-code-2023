#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// i have this cat named shrodinger, he hates and loves mondays

const int kExpansion = 2; // how much an empty row/column expands the map
bool expand(const vector<string>& map, int pos);

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;
    int sum = 0;
    vector<string> map;
    vector<pair<int, int>> galaxies;

    // read map into map and galaxies into galaxies
    while(in) {
        int row = 0;
        while(getline(in, line)) {
            if(line == "") break;

            for(int i = 0; i < line.size(); ++i) {
                if(line[i] == '#') galaxies.push_back(pair<int, int>(row, i));
            }
            map.push_back(line);
            ++row;
        }
    }

    vector<pair<int,int>> offsets(galaxies.size(), pair<int, int>(0, 0));

    // check for row expansion
    for(int i = 0; i < map.size(); ++i) {
        string line = map[i];

        // check for empty row, if empty then all galaxies of higher row are offset
        if(line.find('#') == string::npos) {
            for(int j = 0; j < galaxies.size(); ++j) {
                auto pair = galaxies[j];
                if(pair.first > i) offsets[j].first += kExpansion - 1;
            }
        }
    }

    // check for column expansion
    for(int i = 0; i < map[0].size(); ++i) {
        // check for empty column, if empty then all galaxies of higher column are offset
        if(expand(map, i)) {
            for(int j = 0; j < galaxies.size(); ++j) {
                auto pair = galaxies[j];
                if(pair.second > i) offsets[j].second += kExpansion - 1;
            }
        }
    }

    // add offsets to galaxy coords
    for(int i = 0; i < galaxies.size(); ++i) {
        galaxies[i].first += offsets[i].first;
        galaxies[i].second += offsets[i].second;
    }

    // get distance from each galaxy to other galaxy
    for(int i = 0; i < galaxies.size(); ++i) {
        auto currGalaxy = galaxies[i]; // current 
        for(int j = i + 1; j < galaxies.size(); ++j) {
            auto destGalaxy = galaxies[j]; // destination
            sum += abs(currGalaxy.first - destGalaxy.first) + abs(currGalaxy.second - destGalaxy.second);
        }
    }

    cout << endl << "Sum of distances between galaxies: " << sum << endl;

    return 0;
}

// returns if column is empty
bool expand(const vector<string>& map, int pos) {
    for(const string& line : map) {
        if(line[pos] != '.') return false;
    }
    return true;
}