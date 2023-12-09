#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

// simplicity is portentous

int algorithm(vector<int>& history);

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;
    int sum = 0;

    // read each value history
    while(in) {
        while(getline(in, line)) {
            if(line == "") break;
                vector<int> history;

                istringstream histIn(line);
                // read history into vector
                while(histIn.peek() != -1) {
                    int temp = 0;
                    histIn >> temp;
                    history.push_back(temp);
                }

                int temp = algorithm(history);
                cout << "Next number in sequence: " << temp << endl;

                sum += temp;
        }
    }

    cout << "Sum of extrapolated values: " << sum << endl;

    return 0;
}

// recursion to get extrapolated value
int algorithm(vector<int>& history) {
    int temp = history.front();
    if(count_if(history.begin(), history.end(), [](int a) { return a != 0; }) == 0) return 0;

    for(int i = 0; i < history.size() - 1; ++i) {
        history[i] = (history[i+1] - history[i]);
    }
    history.pop_back();

    return temp - algorithm(history);
}