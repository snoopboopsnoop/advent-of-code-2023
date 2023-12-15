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
    long long sum = 0;

    // read and analyze each spring record
    while(in) {
        while(getline(in, line)) {
            if(line == "") break;

            Node::nodes.clear();
            vector<int> order;
    
            string springs = line.substr(0, line.find(' '));
            string orderStr = line.substr(line.find(' ') + 1);
            
            // also unroll springs and order
            string copySprings = springs;
            string copyOrder = orderStr;
            for(int i = 0; i < 4; ++i) {
                springs += '?' + copySprings;
                orderStr += ',' + copyOrder;
            }

            // do some formatting on input: remove trailing . from spring record
            springs = springs.substr(line.find_first_not_of('.'));
            springs = springs.substr(0, springs.find_last_not_of('.') + 1);

            // i don't think this makes a huge difference, saves cycles though
            for(int i = 0; i < springs.size(); ++i) {
                char c = springs[i];
                if(c == '.') {
                    int pos = springs.find_first_not_of('.', i); // remove superfluous '.'s
                    if(pos != i + 1) {
                        springs.erase(i+1, pos - i - 1);
                    }
                }
            }

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

            long long temp = sum;

            Node node = Node(0, 0);
            sum += node.findNext();

            temp = sum - temp;
            cout << " -> " << temp << ((temp != 1) ? " arrangements" : " arrangement") << endl;
        }
    }

    cout << endl << sum << " total arrangements" << endl;

    return 0;
}