#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// ....|.  <- that's what the difficulty level graph looks like so far

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;
    int sum = 1;
    
    vector<int> times;
    vector<int> distances;

    // times
    getline(in, line);
    line = line.substr(line.find(':')+1);
    istringstream timeIn(line);

    // read times to vector
    while(timeIn.peek() != -1) {
        int temp = 0;
        timeIn >> temp;
        times.push_back(temp);
    }

    // distances
    getline(in, line);
    line = line.substr(line.find(':') + 1);
    istringstream distIn(line);

    // read distances to vector
    while(distIn.peek() != -1) {
        int temp = 0;
        distIn >> temp;
        distances.push_back(temp);
    }

    // go through each race
    for(int i = 0; i < times.size(); ++i) {
        int wins = 0;
        int time = times[i];
        for(int j = 0; j < time; ++j) {
            // valid if time spent held * (total time - time spent held) > record dist
            if(j * (time - j) > distances[i]) {
                wins++;
            }
        }
        cout << wins << " ways to win race " << i + 1 << endl;
        sum *= wins;
    }

    cout << endl << "Total product of ways to win the races: " << sum << endl;

    return 0;
}