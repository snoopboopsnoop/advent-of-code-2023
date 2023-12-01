#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// uh oh i haven't programmed in c++ since may

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;

    string list[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    string first;
    int firstPos = -1;
    string last;
    int lastPos = -1;

    string combined;
    int sum = 0;

    // read sum of calibration document values
    while(in) {
        int currElf = 0;
        while(getline(in, line)) {
            if(line == "") break;

            // get first and last number digits and store them
            firstPos = line.find_first_of("123456789");
            lastPos = line.find_last_of("123456789");

            first = line[firstPos];
            last = line[lastPos];

            // search for each word at front and end
            for(int i = 0; i < sizeof(list)/sizeof(list[0]); ++i) {
                string num = list[i];

                int temp = line.find(num);
                // check if more left than current first
                if(temp != -1 && (temp < firstPos || firstPos == -1)) {
                    firstPos = temp;
                    first = to_string(i+1);
                }

                temp = line.rfind(num);
                // check if more right than current last
                if(temp > lastPos) {
                    lastPos = temp;
                    last = to_string(i+1);
                }
            }

            combined = first + last;
            sum += stoi(combined);
        }
    }

    cout << "Sum of calibration values: " << sum << endl;

    return 0;
}
