#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <sstream>
#include <algorithm>

using namespace std;

// uh oh i haven't programmed in c++ since may

bool valid(const string& check, const vector<int>& order);

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
            
            string springs = line.substr(0, line.find(' '));
            string orderStr = line.substr(line.find(' ') + 1);
            istringstream orderIn(orderStr);

            string intermediate;
            int sumSprings = 0;
            while(getline(orderIn, intermediate, ',')) {
                int temp = stoi(intermediate);
                order.push_back(temp);
                sumSprings += temp;
            }
            //cout << "sum: " << sumSprings << endl;

            int definites = 0;
            int possibleSpaces = 0;

            int brokens = 0;
            
            for(char c : springs) {
                if(c == '#') {
                    definites++;
                }
                else if(c == '?') possibleSpaces++;
            }

            //cout << springs << endl;
            // for(int i : order) {
            //     cout << i << ", ";
            // }
            // cout << endl << endl;

            vector<int> perms(possibleSpaces);
            fill_n(perms.rbegin(), sumSprings - definites, 1);

            // for(int i : perms) {
            //     cout << i << ", ";
            // }
            // cout << endl;

            do {
                string check = springs;
                for(int i : perms) {
                    check[check.find('?')] = (i == 0) ? '.' : '#';
                }

                //cout << "checking string: " << check << endl; 
                if(valid(check, order)) {
                    //cout << "valid pair " << endl;
                    ++sum;
                    validCount++;
                }
            }
            while(next_permutation(perms.begin(), perms.end()));

            //cout << validCount << " valid perms" << endl;
            //cout << endl;
        }
    }

    cout << "Sum of calibration values: " << sum << endl;

    return 0;
}

bool valid(const string& check, const vector<int>& order) {
    int pos = 0;
    for(int i : order) {
        //cout << "checking for " << i << endl;
        for(int j = pos; j < check.size(); ++j) {
            if(check[j] == '.') continue;
            if(find(check.begin() + j, check.begin() + j + i, '.') != check.begin() + j + i) return false;
            else {
                if(j + i < check.size() && check[j+i] != '.') return false;
            }
            pos = j + i + 1;
            break;
        }
    }
    return true;
}