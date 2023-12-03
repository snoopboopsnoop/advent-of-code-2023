#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 3 days 3 parsing problems !!

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;
    int sum = 0;
    vector<string> map;
    // vector that holds coordinates of symbols
    vector<pair<int, int>> symbols;

    // stick data into a 2d vector map and find symbol locations
    while(in) {
        int row = 0;
        while(getline(in, line)) {
            if(line == "") break;

            map.push_back(line);
            // find special symbols in map and save their location to symbols vector
            for(int col = 0; col < line.size(); ++col) {
                if(!isdigit(line[col]) && line[col] != '.') {
                    symbols.push_back(pair<int, int>(row, col));
                }
            }
            ++row;
        }
    }

    // store gear ratios of each symbol 
    vector<pair<int,int>> ratios(symbols.size(), pair<int, int> (0, 1));

    int row = 0;
    // iterate through each row in map and find valid numbers
    for(string line : map) {
        for(int i = 0; i < line.size();) {
            // the number found
            int num = 0;
            // length of the number found
            int len = 1;
            // if digit is found, parse rest of number
            if(isdigit(line[i])) {
                auto end = find_if(line.begin()+i, line.end(), [](char c) {
                    return !isdigit(c);
                });
                len = end - (line.begin()+i);
                num = stoi(line.substr(i, len));         
            }
            else {
                i++;
                continue;
            };

            bool valid = false;
            // which symbol # is being looked at
            int iter = 0;
            // multiply adjacent numbers to corresponding symbol data
            for(auto location : symbols) {
                if(valid) break;
                // is symbol vertically adjacent
                if(abs(location.first-row) > 1) {
                    ++iter;
                    continue;
                }
                else {
                    // is symbol horizontally adjacent
                    if(location.second >= (i - 1 < 0 ? 0 : i - 1) &&
                       location.second <= (i+len > line.size() ? line.size() - 1 : i + len)) {
                        valid = true;
                        // update symbol data
                        ratios[iter].second *= num;
                        ratios[iter].first++;
                    }
                }
                ++iter;
            }
            // iterate by length of number found + 1
            // (because line[len + 1] MUST be a non-digit or end of row)
            i += len + 1;
        }
        ++row;
    }

    // sum gears, which have to have exactly 2 part numbers
    for(int i = 0; i < ratios.size(); ++i) {
        auto curr = ratios[i];
        if(curr.first == 2) {
            cout << "symbol #" << i << " 2 adjacent numbers and a gear ratio of " << curr.second << endl;
            sum += curr.second;
        }
    }

    cout << "Sum of gear ratios: " << sum << endl;

    return 0;
}