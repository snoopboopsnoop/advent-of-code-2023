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
    int validGames = 0;
    
    // analyze each game
    while(in) {
        while(getline(in, game)) {
            if(game == "") break;
            gameNum++;

            istringstream gamestream(game);
            string pull;
            // throw away game number
            gamestream >> pull >> pull;

            bool valid = true;
            // iterate through pulls
            while(getline(gamestream, pull, ';')) {
                istringstream pullstream(pull);
                string block;
                while(getline(pullstream, block, ',')) {
                    // remove leading space
                    block.erase(0, 1);

                    istringstream blockstream(block);
                    int num = 0;
                    string color;
                    // block is format [number] [color]
                    blockstream >> num;
                    blockstream >> color;

                    // check that block counts are valid
                    if(color == "blue" && num > 14) valid = false;
                    else if(color == "green" && num > 13) valid = false;
                    else if(color == "red" && num > 12) valid = false;
                }
            }

            if(valid == true) {
                validGames += gameNum;
                cout << "game " << gameNum << " is valid " << endl;
            }
        }
    }

    cout << "Sum of valid game numbers: " << validGames << endl;

    return 0;
}