#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

#include "Node.cpp"

using namespace std;

// this one is the core memory aoc day

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;
    int sum = 0;

    // read and analyze each spring record
    while(in) {
        while(getline(in, line)) {
            if(line == "") break;

            Node::nodes.clear();
            vector<int> order;

            // do some formatting on input: remove trailing . from spring record
            string springs = line.substr(0, line.find(' '));
            springs = springs.substr(line.find_first_not_of('.'));
            springs = springs.substr(0, springs.find_last_not_of('.') + 1);
            string orderStr = line.substr(line.find(' ') + 1);
            istringstream orderIn(orderStr);

            // put number order in vector
            string intermediate;
            while(getline(orderIn, intermediate, ',')) {
                int temp = stoi(intermediate);
                order.push_back(temp);
            }

            Node::order = order;
            Node::springs = springs;

            cout << Node::springs;

            int temp = sum;
            
            Node node = Node(0, 0);
            sum += node.findNext();
            
            temp = sum - temp;
            cout << " -> " << temp << ((temp != 1) ? " arrangements" : " arrangement") << endl;
        }
    }

    cout << endl << sum << " total arrangements" << endl;

    return 0;
}