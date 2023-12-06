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
    long long sum = 0;

    // times
    getline(in, line);
    line = line.substr(line.find(':') + 1);
    istringstream timeIn(line);

    string time;
    // append times to string and cast to int
    while(timeIn.peek() != -1) {
        string temp;
        timeIn >> temp;
        time = time + temp;
    }
    long long timeInt = stoll(time);

    // distances
    getline(in, line);
    line = line.substr(line.find(':') +1);
    istringstream distIn(line);

    string distance;
    // append distances to string and cast to int
    while(distIn.peek() != -1) {
        string temp;
        distIn >> temp;
        distance = distance + temp;
    }
    long long distanceInt = stoll(distance);

    for(long long j = 0; j < timeInt; ++j) {
        if(j * (timeInt - j) > distanceInt) {
            sum++;
        }
    }

    cout << "Race can be won in " << sum << " ways" << endl;

    return 0;
}