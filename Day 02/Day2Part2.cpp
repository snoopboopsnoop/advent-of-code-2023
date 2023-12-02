#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// i should have paid more attention to the c++1 input stream unit smh

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string game;
    int gameNum = 0;
    int sum = 0;
    
    // analyze each game
    while(in) {
        while(getline(in, game)) {
            if(game == "") break;
            gameNum++;

            istringstream gamestream(game);
            string pull;
            // throw away game number
            gamestream >> pull >> pull;

            int maxRed = 0, maxGreen = 0, maxBlue = 0;
            // iterate through pulls 
            while(getline(gamestream, pull, ';')) {
                istringstream pullstream(pull);
                string block;
                while(getline(pullstream, block, ',')) {
                    block.erase(0, 1);

                    istringstream blockstream(block);
                    int num = 0;
                    string color;
                    // block is format [number] [color]
                    blockstream >> num;
                    blockstream >> color;

                    // check if new highest block requirement
                    if(color == "red" && num > maxRed) maxRed = num;
                    else if(color == "blue" && num > maxBlue) maxBlue = num;
                    else if(color == "green" && num > maxGreen) maxGreen = num;
                }
            }

            int power = (maxBlue * maxRed * maxGreen);
            sum += power;
            cout << "game " << gameNum << " has power " << power << endl;
        }
    }

    cout << "Sum of powers: " << sum << endl;

    return 0;
}