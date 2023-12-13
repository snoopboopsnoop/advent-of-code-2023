#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <sstream>
#include <algorithm>

#include "Node.cpp"

using namespace std;

// uh oh i haven't programmed in c++ since may

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;
    int sum = 0;
    
    // read sum of calibration document values
    while(in) {
        while(getline(in, line)) {
            vector<int> order;
            int validCount = 0;

            if(line == "") break;
            
            string springs = line.substr(line.find_first_not_of('.'), line.find(' ') - 1);
            //cout << springs << endl;
            //cout << "last char at " << springs.find_last_not_of('.') << endl;
            springs = springs.substr(0, springs.find_last_not_of('.') + 1);
            string orderStr = line.substr(line.find(' ') + 1);
            istringstream orderIn(orderStr);

            string intermediate;
            while(getline(orderIn, intermediate, ',')) {
                int temp = stoi(intermediate);
                order.push_back(temp);
            }

            cout << springs << endl;
        }
    }

    cout << "Sum of calibration values: " << sum << endl;

    return 0;
}