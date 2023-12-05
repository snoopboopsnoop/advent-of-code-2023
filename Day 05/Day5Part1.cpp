#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

// dumb ass day 5 biggest difficulty spike ever

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;
    // list of all seed numbers
    vector<unsigned long> seeds;

    while(in) {
        // get list of seed numbers (first line)
        getline(in, line);
        line = line.substr(line.find(':') + 2);
        istringstream seedIn(line);

        // parse each seed number into seeds vector
        while(seedIn.peek() != -1) {
            unsigned long temp = 0;
            seedIn >> temp;
            seeds.push_back(temp);
        }

        // get rid of extra space line
        getline(in, line);

        // read through each map
        while(getline(in, line)) {
            // list of rules <source, dest, range>
            vector<tuple<unsigned long, unsigned long, unsigned long>> map;
            // read each mapping rule
            while(getline(in, line)) {
                // check for end of map
                if(line == "") break;
                
                // read values and save to map
                istringstream itemIn(line);
                unsigned long dest = 0, source = 0, range = 0;

                itemIn >> dest >> source >> range;
                map.push_back(tuple<unsigned long, unsigned long, unsigned long> (source, dest, range));
            }

            int lim = seeds.size();
            // transform each seed through map
            for(int i = 0; i < lim; i++) {
                unsigned long seed = seeds[i];
                for(const auto& rule : map) {
                    // if seed is bigger than the first source value
                    // AND the difference between the seed # and source value is less than the range
                    // then it is transformed by this mapping
                    if(seed >= get<0>(rule) && (seed - get<0>(rule)) <= get<2>(rule)) {
                        cout << "seed " << seed << " maps to " << get<1>(rule) + (seed - get<0>(rule)) << endl;
                        seeds[i] = (get<1>(rule) + (seed - get<0>(rule)));
                        break;
                    }
                }
            }
            cout << endl;
        }
    }

    cout << "Lowest location number: " << *min_element(seeds.begin(), seeds.end()) << endl;

    return 0;
}