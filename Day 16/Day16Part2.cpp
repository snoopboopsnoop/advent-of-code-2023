#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// uh oh i haven't programmed in c++ since may

struct Tile {
    char c;
    int x;
    int y;
    bool activated;
    bool visitedLeft;
    bool visitedRight;

    Tile(char pC, int pX, int pY, bool pActivated) : c(pC), x(pX), y(pY), activated(pActivated), visitedLeft(false), visitedRight(false) {} 
};

struct Beam {
    Tile* tile;
    string direction; // up down left right

    Beam(Tile* tilePtr, const string& dir) : tile(tilePtr), direction(dir) {}
};

int algorithm(Tile* start, const string& startDir, vector<vector<Tile>> map);

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;
    vector<vector<Tile>> map;
    vector<Beam> queue;
    int sum = 0;

    // read map into 2d vector
    while(in) {
        int row = 0;
        while(getline(in, line)) {
            if(line == "") break;
            vector<Tile> temp;

            for(int i = 0; i < line.size(); ++i) {
                temp.push_back(Tile(line[i], i, row, false));
            }

            map.push_back(temp);
            ++row;
        }
    }

    for(const vector<Tile>& line : map){
        for(const Tile& i : line) {
            cout << i.c << ' ';
        }
        cout << endl;
    }


    Tile* start = nullptr;

    // start top row
    for(int i = 0; i < map[0].size(); ++i) {
        start = new Tile('.', i, -1, false);
        int temp = algorithm(start, "down", map);
        delete start;
        if(temp > sum) sum = temp;
        cout << "new best " << sum << endl;

        start = new Tile('.', i, map.size(), false);
        temp = algorithm(start, "up", map);
        delete start;
        start = nullptr;
        if(temp > sum) sum = temp;
        cout << "new best " << sum << endl;
    }

    for(int i = 0; i < map.size(); ++i) {
        start = new Tile('.', -1, i, false);
        int temp = algorithm(start, "right", map);
        delete start;
        if(temp > sum) sum = temp;
        cout << "new best " << sum << endl;
        start = new Tile('.', map[0].size(), i, false);
        temp = algorithm(start, "left", map);
        delete start;
        start = nullptr;
        if(temp > sum) sum = temp;
        cout << "new best " << sum << endl;
    }

    cout << "Sum of calibration values: " << sum << endl;

    return 0;
}

int algorithm(Tile* start, const string& startDir, vector<vector<Tile>> map) {
    int sum = 0;

    vector<Beam> queue;

    queue.push_back(Beam(start, startDir));

    while(queue.size() != 0) {
        // for(Beam i : queue) {
        //     cout << "(" << i.tile->x << ", " << i.tile->y << ")" << ", " << i.direction << endl;
        // }
        // cout << endl;

        Beam curr = queue.front();
        int posX = curr.tile->x;
        int posY = curr.tile->y;

        if(curr.direction == "up") {
            posY -= 1;
            while(posY >= 0) {
                Tile* tile = &map[posY][posX];
                tile->activated = true;
                if(tile->c == '-') {
                    if(!tile->visitedLeft && !tile->visitedRight) {
                        queue.push_back(Beam(tile, "left"));
                        queue.push_back(Beam(tile, "right"));
                        tile->visitedLeft = true;
                    }
                    break;
                }
                else if(tile->c == '/') {
                    if(!tile->visitedRight) {
                        queue.push_back(Beam(tile, "right"));
                        tile->visitedRight = true;
                    }
                    break;
                }
                else if(tile->c == '\\') {
                    if(!tile->visitedLeft) {
                        queue.push_back(Beam(tile, "left"));
                        tile->visitedLeft = true;
                    }
                    break;
                }
                --posY;
            }
        }
        else if(curr.direction == "down") {
            posY += 1;
            while(posY < map.size()) {
                Tile* tile = &map[posY][posX];
                tile->activated = true;
                if(tile->c == '-') {
                    if(!tile->visitedLeft) {
                        queue.push_back(Beam(tile, "left"));
                        queue.push_back(Beam(tile, "right"));
                        tile->visitedLeft = true;
                    }
                    break;
                }
                else if(tile->c == '/') {
                    if(!tile->visitedLeft) {
                        queue.push_back(Beam(tile, "left"));
                        tile->visitedLeft = true;
                    }
                    break;
                }
                else if(tile->c == '\\') {
                    if(!tile->visitedRight) {
                        queue.push_back(Beam(tile, "right"));
                        tile->visitedRight = true;
                    }
                    break;
                }
                ++posY;
            }
        }
        else if(curr.direction == "right") {
            posX += 1;
            while(posX < map.size()) {
                Tile* tile = &map[posY][posX];
                tile->activated = true;
                if(tile->c == '|') {
                    if(!tile->visitedLeft) {
                        queue.push_back(Beam(tile, "up"));
                        queue.push_back(Beam(tile, "down"));
                        tile->visitedLeft = true;
                    }
                    break;
                }
                else if(tile->c == '/') {
                    if(!tile->visitedLeft) {
                        queue.push_back(Beam(tile, "up"));
                        tile->visitedLeft = true;
                    }
                    break;
                }
                else if(tile->c == '\\') {
                    if(!tile->visitedLeft) {
                        queue.push_back(Beam(tile, "down"));
                        tile->visitedLeft = true;
                    }
                    break;
                }
                ++posX;
            }
        }
        else if(curr.direction == "left") {
            posX -= 1;
            while(posX >= 0) {
                Tile* tile = &map[posY][posX];
                tile->activated = true;
                if(tile->c == '|') {
                    if(!tile->visitedLeft) {
                        queue.push_back(Beam(tile, "up"));
                        queue.push_back(Beam(tile, "down"));
                        tile->visitedLeft = true;
                    }
                    break;
                }
                else if(tile->c == '/') {
                    if(!tile->visitedRight) {
                        queue.push_back(Beam(tile, "down"));
                        tile->visitedRight = true;
                    }
                    break;
                }
                else if(tile->c == '\\') {
                    if(!tile->visitedRight) {
                        queue.push_back(Beam(tile, "up"));
                        tile->visitedRight = true;
                    }
                    break;
                }
                --posX;
            }
        }

        queue.erase(queue.begin());
    }

    for(const vector<Tile>& line : map) {
        for(Tile tile : line) {
            if(tile.activated == true) {
                //cout << "energized: " << tile.x << ", " << tile.y << endl;
                ++sum;
            }
        }
    }

    return sum;
}