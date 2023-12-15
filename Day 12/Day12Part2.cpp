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
        int row = 0;
        while(getline(in, line)) {
            vector<int> order;
            int validCount = 0;

            if(line == "") break;

            cout << "base springs: " << line << endl;
            string springs = line.substr(0, line.find(' '));
            //cout << "springs w/ end chopped: " << springs << "end" << endl;
            string orderStr = line.substr(line.find(' ') + 1);
            

            // string copySprings = springs;
            // string copyOrder = orderStr;
            // for(int i = 0; i < 4; ++i) {
            //     springs += '?' + copySprings;
            //     orderStr += ',' + copyOrder;
            // }

            springs = springs.substr(line.find_first_not_of('.'));
            //cout << "springs after snipping ends " << springs << "end" << endl;
            // cout << springs << endl;
            //cout << "last char at " << springs.find_last_not_of('.') << endl;
            springs = springs.substr(0, springs.find_last_not_of('.') + 1);
            cout << "springs after snipping ends " << springs << "end" << endl;

            istringstream orderIn(orderStr);

            string intermediate;
            int minChar = 0;
            while(getline(orderIn, intermediate, ',')) {
                int temp = stoi(intermediate);
                order.push_back(temp);
                minChar += temp + 1;
            }
            --minChar;

            Node::order = order;
            Node::springs = springs;

            cout << Node::springs << endl;
            for(int i : order) {
                cout << i << ",";
            }
            cout << endl;

            int temp = Node::arrangements;

            Node node = Node(0, 0, minChar);
            //node.findNext();

            int total = Node::arrangements - temp;
            
            cout << "row " << row << ": " << total << " perms" << endl;
            //cout << Node::arrangements << " total arrangements" << endl << endl;
            ++row;
            cout << endl;
        }
    }

    cout << "Sum of calibration values: " << Node::arrangements << endl;

    return 0;
}