#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// needed this one after day 12

int findSymmetry(const vector<string>& map);
void rotate(vector<string>& map);

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;
    int sum = 0;
    
    // read each map and get values
    while(in) {
        vector<string> map;

        while(getline(in, line)) {
            if(line == "") break;
            map.push_back(line);
        }

        for(string i : map) {
            cout << i << endl;
        }

        int rowsAbove = findSymmetry(map);
        

        rotate(map); // rotate 90 degrees clockwise so the same algorithm will work

        int columnsLeft = findSymmetry(map);

        if(columnsLeft == 0) cout << rowsAbove << ((rowsAbove != 1) ? " rows " : " row ") << "above line of symmetry" << endl << endl;
        else cout << columnsLeft << ((columnsLeft == 0) ? " columns " : " column ") << "above line of symmetry" << endl << endl;
        
        sum += 100 * rowsAbove + columnsLeft;
    }

    cout << "Note summmary: " << sum << endl;

    return 0;
}

// returns number of columns or rows before the line of symmetry
int findSymmetry(const vector<string>& map) {
    for(int i = 0; i < map.size(); ++i) {
        string line = map[i];
        
        //check for even reflection
        if(i + 1 < map.size() && line == map[i+1]) {
            int leftPos = i;
            int rightPos = i + 1;

            // spread out to check
            do {
                --leftPos;
                ++rightPos;

                if(leftPos < 0 || rightPos >= map.size()) return i + 1;
            }
            while(map[leftPos] == map[rightPos]);
        }
    }
    return 0;
}

// rotates map 90 degrees clockwise
void rotate(vector<string>& map) {
    vector<string> temp(map[0].size());

    for(int i = map.size() - 1; i >= 0; --i) {
        string line = map[i];
        for(int j = 0; j < line.size(); ++j) {
            temp[j].push_back(line[j]);
        }
    }

    map = temp;
}