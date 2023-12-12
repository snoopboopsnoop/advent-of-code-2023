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
int algorithm(const string& springs, const string& orderStr);
void shrink(string&springs, vector<int>& order);

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;
    int sum = 0;
    
    // read sum of calibration document values
    while(in) {
        int row = 1;
        while(getline(in, line)) {
            cout << row << endl;
            //cout << "bobrbobrbobrbobrbobrbobrbobrbobrbobrbobrbobrbobr" << endl;

            if(line == "") break;
            
            string springs = line.substr(0, line.find(' '));
            string orderStr = line.substr(line.find(' ') + 1);

            cout << springs << endl;
            cout << orderStr << endl;
            int temp = algorithm(springs, orderStr);
            cout << "n = 0: " << temp << endl << endl;

            string springs2 = springs;
            string orderStr2 = orderStr;

            for(int i = 0; i < 2; ++i) {
                springs2 += '?' + springs;
                orderStr2 += ',' + orderStr;
                
                cout << springs2 << endl;
                cout << orderStr2 << endl;
                cout << "n = 1: " << algorithm(springs2, orderStr2) << endl;
                cout << endl;
            }

            ++row;
        }
    }

    cout << "Sum of calibration values: " << sum << endl;

    return 0;
}

bool valid(const string& check, const vector<int>& order) {
    int pos = 0;
    for(int i : order) {
        //cout << "checking for " << i << endl;
        int size = check.size();
        for(int j = pos; j < size; ++j) {
            if(check[j] == '.') continue;
            if(find(check.begin() + j, check.begin() + j + i, '.') != check.begin() + j + i) return false;
            else {
                if(j + i < size && check[j+i] != '.') return false;
            }
            pos = j + i + 1;
            break;
        }
    }
    return true;
}

void shrink(string&springs, vector<int>& order) {
    
}

int algorithm(const string& springs, const string& orderStr) {
    vector<int> order;
    int validCount = 0;

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

    vector<int> perms(possibleSpaces);
    fill_n(perms.rbegin(), sumSprings - definites, 1);

    do {
        string check = springs;
        for(int i : perms) {
            check[check.find('?')] = (i == 0) ? '.' : '#';
        }

        //cout << "checking string: " << check << endl; 
        if(valid(check, order)) {
            cout << "valid " << check << endl;
            validCount++;
        }
    }
    while(next_permutation(perms.begin(), perms.end()));

    return validCount;

}