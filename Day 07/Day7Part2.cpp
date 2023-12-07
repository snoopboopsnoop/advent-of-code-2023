#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <map>

using namespace std;

// blackjack but cringe call me jack black

// returns true if a > b, returns false if a < b (by the instructions, a cannot be equal to b)
bool compareHands(const pair<string, int>& a, const pair<string, int>& b);
// maps non-digits to correct char value
char convert(char c);
// returns type of hand, 0 being best and 6 being worst
int getType(const string& hand);

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;
    int sum = 0;
    vector<pair<string, int>> hands;
    
    // read each hand and bid and store in vector
    while(in) {
        while(getline(in, line)) {
            if(line == "") break;

            string hand = line.substr(0, line.find(' '));
            int bid = stoi(line.substr(line.find(' ')+1));

            hands.push_back(pair<string, int>(hand, bid));
        }
    }

    sort(hands.begin(), hands.end(), compareHands);

    // calculate total winnings
    const size_t vSize = hands.size();
    for(int i = 0; i < vSize; ++i) {
        auto curr = hands[i];
        cout << "hand " << curr.first << " worth " << curr.second << endl;
        sum += curr.second * (vSize - i);
    }

    cout << "Total winnings: " << sum << endl;

    return 0;
}

bool compareHands(const pair<string, int>& a, const pair<string, int>& b) {
    string first = a.first;
    string second = b.first;
    
    int firstType = getType(first);
    int secondType = getType(second);

    if(firstType < secondType) return true;
    else if(firstType > secondType) return false;
    
    // if same type, compare characters by index
    for(int i = 0; i < first.size(); ++i) {
        char currFirst = convert(first[i]);
        char currSecond = convert(second[i]);

        if(currFirst == currSecond) continue;
        return currFirst > currSecond;
    }
}

char convert(char c) {
    switch(c) {
        case 'A':
            return '>';
            break;
        case 'K':
            return '=';
            break;
        case 'Q':
            return '<';
            break;
        case 'J':
            return '1';
            break;
        case 'T':
            return ':';
            break;
        default:
            return c;
    }
}

int getType(const string& hand) {
    map<char, int> map; //maps char to number of times in hand

    for(char i : hand) {
        try {
            map.at(i)++; //increment char count
        }
        catch(out_of_range) {
            map.insert(pair<char, int>(i, 1)); //add char to map if doesn't exist
        }
    }

    // get most common card, add number of jacks to it to maximize hand type
    auto biggest = *max_element(map.begin(), map.end(), [] (const pair<char, int>& a, const pair<char, int>& b){
        if(a.first == 'J') return true; //jacks can't be most common
        else if(b.first == 'J') return false;
        return a.second < b.second;
    });

    if(map.find('J') != map.end()) {
        int temp = map.at('J');
        if(!(temp == 5)) { //JJJJJ edge case, can't erase map to jacks if the map is only jacks
            map.at(biggest.first) += temp;
            map.erase('J');
        }
    }

    int size = map.size();
    switch(size) {
        case 1: return 0; //5 of a kind
        case 2: //4 of a kind or full house
            {
                int num1 = map.begin()->second;
                int num2 = (++map.begin())->second;

                if((num1 == 4 && num2 == 1) || (num1 == 1 && num2 == 4)) return 1; //four of a kind
                else return 2; //otherwise has to be full house
            }
        case 3: //3 of a kind or two pair
            {
                auto iter = map.begin();
                int num1 = iter->second;
                ++iter;
                int num2 = iter->second;
                ++iter;
                int num3 = iter->second;

                if(num1 == 2 || num2 == 2 || num3 == 2) return 4; //has to have 2 of a kind to be a 2 pair
                else return 3; //otherwise 3 of a kind
            }
        case 4: return 5; //one pair
        case 5: return 6; //high card
    }
    return -1;
}