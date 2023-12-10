#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// today is the one day of aoc where i have fun playing w the output

void checkNeighbor(vector<pair<int, int>>& queue, const pair<int, int>& location, const string& direction, const vector<string>& map);
void cycle(vector<pair<int, int>>& queue, vector<string>& map, int dist);

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;
    int sum = 0;
    vector<string> map;
    pair<int, int> start; // y, x (index 0 start)

    // read map into map
    while(in) {
        int row = 0;
        while(getline(in, line)) {
            if(line == "") break;

            if(line.find('S') != string::npos) start = pair<int, int>(row, line.find('S'));
            map.push_back(line);
            ++row;
        }
    }

    vector<pair<int, int>> queue = { start };
    
    int dist = -1;
    // flood algorithm
    while(queue.size() != 0) {
        ++dist;

        int size = queue.size();
        for(int i = 0; i < size; ++i) {
            cycle(queue, map, dist);
        }
    }

    for(string i : map) {
        cout << i << endl;
    }

    cout << endl << "Farthest point along the loop is " << dist << " steps away" << endl;

    return 0;
}

// pulls front of queue and adds connected neighbors to back of queue
void cycle(vector<pair<int, int>>& queue, vector<string>& map, int dist) {
    pair<int, int> curr = queue.front();
    char currChar = map[curr.first][curr.second];

    // this is so cringe
    if(currChar == 'S') {
        checkNeighbor(queue, curr, "up", map);
        checkNeighbor(queue, curr, "down", map);
        checkNeighbor(queue, curr, "left", map);
        checkNeighbor(queue, curr, "right", map);
    }
    else if(currChar == '|') {
        checkNeighbor(queue, curr, "up", map);
        checkNeighbor(queue, curr, "down", map);
    }
    else if(currChar == '-') {
        checkNeighbor(queue, curr, "left", map);
        checkNeighbor(queue, curr, "right", map);
    }
    else if(currChar == 'L') {
        checkNeighbor(queue, curr, "up", map);
        checkNeighbor(queue, curr, "right", map);
    }
    else if(currChar == 'J') {
        checkNeighbor(queue, curr, "up", map);
        checkNeighbor(queue, curr, "left", map);
    }
    else if(currChar == '7') {
        checkNeighbor(queue, curr, "down", map);
        checkNeighbor(queue, curr, "left", map);
    }
    else if(currChar == 'F') {
        checkNeighbor(queue, curr, "down", map);
        checkNeighbor(queue, curr, "right", map);
    }

    map[curr.first][curr.second] = 'X';

    queue.erase(queue.begin());
}

// checks neighbor; if connected, add to queue
void checkNeighbor(vector<pair<int, int>>& queue, const pair<int, int>& location, const string& direction, const vector<string>& map) {
    if(direction == "up" && location.first - 1 >= 0) {
        char upChar = map[location.first - 1][location.second];
        if (upChar == '|' || upChar == '7' || upChar == 'F') queue.push_back(pair<int, int>(location.first - 1, location.second));
    }
    else if(direction == "left" && location.second - 1 >= 0) {
        char leftChar = map[location.first][location.second - 1];
        if (leftChar == '-' || leftChar == 'L' || leftChar == 'F') queue.push_back(pair<int, int>(location.first, location.second - 1));
    }
    else if(direction == "right" && location.second + 1 < map[0].size()) {
        char rightChar = map[location.first][location.second + 1];
        if (rightChar == '-' || rightChar == 'J' || rightChar == '7') queue.push_back(pair<int, int>(location.first, location.second + 1));
    }
    else if(direction == "down" && location.first + 1 < map.size()) {
        char downChar = map[location.first + 1][location.second];
        if (downChar == '|' || downChar == 'L' || downChar == 'J') queue.push_back(pair<int, int>(location.first + 1, location.second));
    }
}