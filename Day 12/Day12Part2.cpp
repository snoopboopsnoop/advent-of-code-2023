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

bool simplify(vector<int>& order, string& springs);
bool simplifyLeft(vector<int>& order, string& springs);
bool simplifyRight(vector<int>& order, string& springs);

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

bool simplify(vector<int>& order, string& springs) {
    cout << springs << endl;

    bool altered = simplifyLeft(order, springs);
    cout << springs << endl;
    altered = simplifyRight(order, springs) ? 1 : altered;

    return altered;
}

bool simplifyLeft(vector<int>& order, string& springs) {
    bool altered = false;

    // from left
    int curr = order.front();
    int front = springs.front();
    int end = springs.find('.');
    int first = springs.find('#');
    int last = (end != string::npos) ? springs.find_last_of('#', end) : -1;
    
    if(springs.size() == curr) {
        springs.clear();
        order.clear();
    }

    cout << "checking left edge" << endl;


    if(springs[0] == '#') {
        springs.erase(springs.begin(), springs.begin() + curr + 1);
        order.erase(order.begin());
        altered = true; 
    }

    if(end == curr) {
        springs.erase(springs.begin(), springs.begin() + curr + 1);
        order.erase(order.begin());
        altered = true;
    }

    else if(springs[0] == '?' && springs[1] == '#') {
        if(find_if(springs.begin() + 1, springs.begin() + curr + 1, [](char c) { return c != '#'; }) == springs.begin() + curr + 1) {
            springs.erase(springs.begin(), springs.begin() + curr + 2);
            order.erase(order.begin());
            altered = true;
        }
    }

    return altered;
}

bool simplifyRight(vector<int>& order, string& springs) {
    bool altered = false;

    cout << "checking rigth edge" << endl;
    // from right
    int curr = order.back();
    int front = springs.rfind('.') + 1;
    int end = springs.size() - 1;
    int first = springs.find('#', front);
    int last = springs.find_last_of('#');

    if(front != 0) {
        if(end - front + 1 == curr) {
            auto found = find_if(springs.rbegin() + (end - front + 1), springs.rend(), [] (char c) { return c != '.'; });
            int pos = (found).base() - springs.begin();
            springs.erase(springs.begin() + pos, springs.end());
            order.pop_back();
            altered = true;
        }

        else if(springs[springs.size() - 1] == '?' && springs[springs.size() - 2] == '#') {
            if(find_if(springs.rbegin() + 1, springs.rbegin() + curr + 1, [](char c){ return c != '#'; }) == springs.rbegin() + curr + 1) {
                springs.erase((springs.rbegin() + curr + 2).base(), springs.end());
                order.pop_back();
                altered = true;
            }
        }
    }

    return altered;
}