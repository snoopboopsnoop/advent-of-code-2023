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
    ifstream lineReader("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;
    int sum = 0;
    
    // keeps track of how many of each card you have { # of card 1s, # of card 2s, # of card 3s, etc. }
    vector<int> cardNums(count(istreambuf_iterator<char>(lineReader), istreambuf_iterator<char>(), '\n')+1, 1);

    // read each card
    while(in) {
        int card = 1;
        while(getline(in, line)) {
            if(line == "") break;

            // how many winning numbers
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

                if(find(winningNums.begin(), winningNums.end(), temp) != winningNums.end()) score += 1;
            }
            
            cout << "You have " << cardNums[card - 1] << ((cardNums[card - 1] != 1) ? " copies of card " : " copy of card ") << card << endl;
            for(int i = 0; i < score; ++i) {
                cout << "\tWon a copy of card " << i + card + 1 << endl;
                cardNums[card + i] += cardNums[card - 1];
            }
            cout << endl;
            card++;
        }

        for(int i : cardNums) {
            sum += i;
        }
    }

    cout << "You end up with " << sum << " total scratchcards" << endl;

    return 0;
}