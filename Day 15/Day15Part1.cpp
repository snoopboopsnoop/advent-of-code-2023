#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

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
    getline(in, line);

    istringstream sin(line);

    string token;
    while(getline(sin, token, ',')) {
        cout << token << endl;

        int hash = 0;
        for(char c : token) {
            hash += c;
            hash *= 17;
            hash = hash % 256;
        }
        sum += hash;
    }

    cout << "Sum of calibration values: " << sum << endl;

    return 0;
}