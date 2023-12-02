#include <iostream>
#include <fstream>
#include <string>

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
            if(line == "") break;

            string combined;
            // append first int
            combined += line[line.find_first_of("0123456789")];
            // second int
            combined += line[line.find_last_of("0123456789")];

            sum += stoi(combined);
        }
    }

    cout << "Sum of calibration values: " << sum << endl;

    return 0;
}
