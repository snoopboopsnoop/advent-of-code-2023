#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// man i had a stroke doing this one wtf

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;
    int sum = 0;
    
    // read each card
    while(in) {
        int card = 1;
        while(getline(in, line)) {
            if(line == "") break;

            // card's points
            int score = 0;
            // list of winning numbers
            vector<int> winningNums;

            // separate winning nums and player nums
            int sep = line.find("|");
            string winning = line.substr(0, sep - 1);
            string nums = line.substr(sep + 2);
            // get rid of beginning 'card #' text
            winning = winning.substr(winning.find(':') + 1);

            istringstream winstream(winning);
            istringstream numstream(nums);

            // write winning nums to vector
            while(winstream.peek() != -1) {
                int temp = 0;
                winstream >> temp;
                winningNums.push_back(temp);
            }

            // check nums against winningNums to get score
            while(numstream.peek() != -1) {
                int temp = 0;
                numstream >> temp;

                if(find(winningNums.begin(), winningNums.end(), temp) != winningNums.end()) {
                    if(score == 0) {
                        score = 1;
                    }
                    else score *= 2;
                }
            }

            cout << "Card " << card << " is worth " << score << " points" << endl;
            sum += score;
            ++card;
        }
    }

    cout << "The large pile of colorful cards is worth " << sum << " points" << endl;

    return 0;
}