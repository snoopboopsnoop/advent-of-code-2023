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

int sum = 0;

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;
    vector<vector<Tile>> map;
    vector<Beam> queue;

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

    Tile* start = new Tile('.', -1, 0, false);

    queue.push_back(Beam(start, "right"));
    map[0][0].activated = true;
    
    while(queue.size() != 0) {
        for(Beam i : queue) {
            cout << "(" << i.tile->x << ", " << i.tile->y << ")" << ", " << i.direction << endl;
        }
        cout << endl;

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
                cout << "energized: " << tile.x << ", " << tile.y << endl;
                ++sum;
            }
        }
    }

    delete start;

    cout << "Sum of calibration values: " << sum << endl;

    return 0;
}