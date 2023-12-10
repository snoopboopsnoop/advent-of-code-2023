#define _O_U16TEXT 0x00020000 // for some reason this isn't predefined, thank you stack overflow man

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <fcntl.h> // all includes below this are to let me print color and unicode
#include <io.h> // an indian man on youtube taught me how to do this
#include <windows.h>

using namespace std;

// today is the one day of aoc where i have fun playing w the output

bool checkNeighbor(vector<pair<int, int>>& queue, const pair<int, int>& location, const string& direction, const vector<string>& map);
void cycle(vector<pair<int, int>>& queue, vector<string>& map, vector<string>& map2, int dist);
int countIntersect(const string& line, int pos);

int main() {
    // for printing color
    HANDLE hc = GetStdHandle(STD_OUTPUT_HANDLE);

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

    vector<string> map2(map.size(), string(map[0].size(), 'X')); // second map that will only contain loop pipes
    vector<pair<int, int>> queue = { start };
    
    int dist = -1;
    // flood algorithm
    while(queue.size() != 0) {
        ++dist;

        int size = queue.size();
        for(int i = 0; i < size; ++i) {
            cycle(queue, map, map2, dist);
        }
    }

    int row = 0;
    // checks each X to see if inside using ray casting
    for(string& line : map2) {
        for(int i = 0; i < line.size(); ++i) {
            if(line[i] == 'X') {
                if(countIntersect(line, i) % 2 != 0) {
                    ++sum;
                }
                else line[i] = ' ';
            }
        }
        ++row;
    }

    // pretty printing pipe loop
    _setmode(_fileno(stdout), _O_U16TEXT);
    for(string i : map2) {
        for(char c : i) {
            switch(c) {
                case '|':
                    wprintf(L"\x2503");
                    break;
                case '-':
                    wprintf(L"\x2501");
                    break;
                case 'L':
                    wprintf(L"\x2517");
                    break;
                case 'J':
                    wprintf(L"\x251b");
                    break;
                case '7':
                    wprintf(L"\x2513");
                    break;
                case 'F':
                    wprintf(L"\x250F");
                    break;
                case 'X':
                    SetConsoleTextAttribute(hc, 0x0A);
                    wprintf(L"\x2588"); 
                    SetConsoleTextAttribute(hc, 7);
                    break;
                default:
                    wprintf(L"%c", c);
                    break;
            }
        }
        wprintf(L"\n");
    }

    wprintf(L"%i enclosed tiles\n", sum);

    return 0;
}

// ray cast
int countIntersect(const string& line, int pos) {
    int crosses = 0;
    // start from left and cast until point
    for(int i = 0; i < pos; ++i) {
        if(line[i] == '|') {
            ++crosses; // every vertical line has to be a crossed line
        }
        // this whole else if basically just checks for vertical lines at the same y level as the point
        // if the turns are matching (F7 or LJ) then it's not a crossed line, if they're opposite (FJ or L7)
        // then they count as a crossed line
        else if(line[i] == 'F' || line[i] == 'L') { 
            int end7 = line.find('7', i);
            int endJ = line.find('J', i);

            if(end7 == string::npos) end7 = endJ + 1;
            else if(endJ == string::npos) endJ = end7 + 1;

            if(end7 < endJ) {
                if(line[i] == 'L') ++crosses;
                i += end7 - i;
            }
            else if(end7 > endJ) {
                if(line[i] == 'F') ++crosses;
                i += endJ - i;
            }
        }
    }
    return crosses;
}

// pulls front of queue and adds connected neighbors to back of queue
void cycle(vector<pair<int, int>>& queue, vector<string>& map, vector<string>& map2, int dist) {
    pair<int, int> curr = queue.front();
    char currChar = map[curr.first][curr.second];

    string checkS;

    // this is so cringe
    if(currChar == 'S') {
        if(checkNeighbor(queue, curr, "up", map)) {
            checkS += 'U';
        }
        if(checkNeighbor(queue, curr, "down", map)) {
            checkS += 'D';
        }
        if(checkNeighbor(queue, curr, "left", map)) {
            checkS += 'L';
        }
        if(checkNeighbor(queue, curr, "right", map)) {
            checkS += 'R';
        }
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

    // how did i make it more cringe (this just replaces S with the correct pipe)
    if(currChar == 'S') {
        if(checkS == "UD") map2[curr.first][curr.second] = '|';
        else if(checkS == "UL") map2[curr.first][curr.second] = 'J';
        else if(checkS == "UR") map2[curr.first][curr.second] = 'L';
        else if(checkS == "DL") map2[curr.first][curr.second] = '7';
        else if(checkS == "DR") map2[curr.first][curr.second] = 'F';
    }

    else if (currChar != 'X'){
        map2[curr.first][curr.second] = map[curr.first][curr.second];
    }

    map[curr.first][curr.second] = 'X';

    queue.erase(queue.begin());
}

// checks neighbor; if connected, add to queue, also returns if it was a neighbor for starting S condition
bool checkNeighbor(vector<pair<int, int>>& queue, const pair<int, int>& location, const string& direction, const vector<string>& map) {
    if(direction == "up" && location.first - 1 >= 0) {
        char upChar = map[location.first - 1][location.second];
        if (upChar == '|' || upChar == '7' || upChar == 'F') {
            queue.push_back(pair<int, int>(location.first - 1, location.second));
            return true;
        }
    }
    else if(direction == "left" && location.second - 1 >= 0) {
        char leftChar = map[location.first][location.second - 1];
        if (leftChar == '-' || leftChar == 'L' || leftChar == 'F') {
            queue.push_back(pair<int, int>(location.first, location.second - 1));
            return true;
        }
    }
    else if(direction == "right" && location.second + 1 < map[0].size()) {
        char rightChar = map[location.first][location.second + 1];
        if (rightChar == '-' || rightChar == 'J' || rightChar == '7') {
            queue.push_back(pair<int, int>(location.first, location.second + 1));
            return true;
        }
    }
    else if(direction == "down" && location.first + 1 < map.size()) {
        char downChar = map[location.first + 1][location.second];
        if (downChar == '|' || downChar == 'L' || downChar == 'J') {
            queue.push_back(pair<int, int>(location.first + 1, location.second));
            return true;
        }
    }
    return false;
}