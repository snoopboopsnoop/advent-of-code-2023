#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// uh oh i haven't programmed in c++ since may

int findSymmetry(const vector<string>& map);
void rotate(vector<string>& map);

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;
    int sum = 0;
    
    // read sum of calibration document values
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
        cout << rowsAbove << " rows above line of symmertry" << endl;

        rotate(map);

        int columnsLeft = findSymmetry(map);
        cout << columnsLeft << " columns above line of symmetry" << endl << endl;
        
        sum += 100 * rowsAbove + columnsLeft;
    }

    cout << "Sum of calibration values: " << sum << endl;

    return 0;
}

int findSymmetry(const vector<string>& map) {
    for(int i = 0; i < map.size(); ++i) {
        string line = map[i];
        
        //check for even reflection
        if(i + 1 < map.size() && line == map[i+1]) {
            int leftPos = i;
            int rightPos = i + 1;

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

void rotate(vector<string>& map) {
    vector<string> temp(map[0].size());

    for(int i = map.size() - 1; i >= 0; --i) {
        string line = map[i];
        for(int j = 0; j < line.size(); ++j) {
            temp[j].push_back(line[j]);
        }
    }
    
    // for(string line : temp) {
    //     cout << line << endl;
    // }
    // cout << endl;

    map = temp;
}