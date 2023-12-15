#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <sstream>
#include <algorithm>

using namespace std;

struct Node {
    static long long arrangements;
    static vector<int> order;
    static string springs;

    int num; // which number to look for
    int orderPos;
    int springPos; // which index of the string does this node start with
    int sumGroups; // keeps track of minimum number of characters required

    Node(int paramOPos, int paramSPos, int sum) {
        //nodes.erase(nodes.begin());

        orderPos = paramOPos;
        num = order[orderPos];
        springPos = paramSPos;
        if(orderPos != 0) sumGroups = sum - order[orderPos - 1] - 1;
        else sumGroups = sum;

        for(int i = 0; i < orderPos; ++i) {
            cout << " ";
        }
        cout << "new Node created looking for index " << orderPos <<  " in order vector(" << num << "), in string " << springs.substr(springPos) << endl;

        if(!(springs.size() - springPos < sumGroups)) findNext();
        //if(currArrange != 0) cout << currArrange << " local arrangements" << endl;
        //cout << endl;
    }


    void findNext() {
        size_t lineSize = springs.size();
        for(int i = springPos; i + num <= lineSize; ++i) {
            //cout << "spring size: " << springs.size() << endl;
            if(springs[i] != '.') {
                for(int i = 0; i < orderPos; ++i) {
                    cout << "\t";
                }
                cout << "looking at char " << springs[i] << " at pos " << i << endl;   
                //cout << "possible" << endl;
                if(find(springs.begin() + i, springs.begin() + i + num, '.') == springs.begin() + i + num) {
                    cout << "range works" << endl;
                    if((i + num) == lineSize || springs[i + num] == '.' || springs[i + num] == '?') {
                        if(i == 0 || springs[i - 1] == '.' || springs[i - 1] == '?') {

                            if(orderPos + 1 == order.size()) {
                                if(find(springs.begin() + num + i, springs.end(), '#') == springs.end()) {
                                    for(int i = 0; i < orderPos; ++i) {
                                        cout << " ";
                                    }
                                    cout << "found path" << endl;
                                    ++arrangements;
                                }
                                if(springs[i] == '#') break;
                                continue;
                            } 

                            int temp = i + num + 1;
                            
                            auto check = find_if(springs.begin() + temp, springs.end(), [] (char c) { return (c != '.'); });
                            if(check != springs.end()) temp = check - springs.begin();
                            
                            if((temp + num) <= lineSize) {
                                //cout << "new string starts at pos " << temp << endl;
                                Node node = Node(orderPos + 1, temp, sumGroups);
                            }
                        }
                    }
                }
                if(springs[i] == '#') break;
            }
        }
    }
};

long long Node::arrangements = 0;
vector<int> Node::order;
string Node::springs;