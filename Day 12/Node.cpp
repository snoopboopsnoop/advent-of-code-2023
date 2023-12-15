#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <sstream>
#include <algorithm>

using namespace std;

struct Node {
    static vector<int> order;
    static string springs;
    static vector<Node> nodes;

    int num; // which number to look for
    int orderPos;
    int springPos; // which index of the string does this node start with
    int sumGroups; // keeps track of minimum number of characters required
    int localSum; // arrangements from this node

    Node(int paramOPos, int paramSPos, int sum) {
        //nodes.erase(nodes.begin());

        localSum = 0;
        orderPos = paramOPos;
        num = order[orderPos];
        springPos = paramSPos;
        if(orderPos != 0) sumGroups = sum - order[orderPos - 1] - 1;
        else sumGroups = sum;

        // for(int i = 0; i < orderPos; ++i) {
        //     cout << " ";
        // }
        // cout << springs.substr(springPos) << " (" << num << ")" << endl;
        //if(currArrange != 0) cout << currArrange << " local arrangements" << endl;
        //cout << endl;
    }


    int findNext() {
        if(springs.size() - springPos < sumGroups) return 0;

        size_t lineSize = springs.size();
        for(int i = springPos; i + num <= lineSize; ++i) {
            //cout << "spring size: " << springs.size() << endl;
            if(springs[i] != '.') {
                // for(int i = 0; i < orderPos; ++i) {
                //     cout << "\t";
                // }
                // cout << "looking at char " << springs[i] << " at pos " << i << endl;   
                //cout << "possible" << endl;
                if(find(springs.begin() + i, springs.begin() + i + num, '.') == springs.begin() + i + num) {
                    //cout << "range works" << endl;
                    if((i + num) == lineSize || springs[i + num] == '.' || springs[i + num] == '?') {
                        //cout << "end works" << endl;
                        if(i == 0 || springs[i - 1] == '.' || springs[i - 1] == '?') {
                            //cout << "beg works" << endl;
                            if(orderPos + 1 == order.size()) {
                                if(find(springs.begin() + num + i, springs.end(), '#') == springs.end()) {
                                    // for(int i = 0; i < orderPos; ++i) {
                                    //     cout << " ";
                                    // }
                                    // cout << "found path" << endl;
                                    ++localSum;
                                }
                                if(springs[i] == '#') break;
                                continue;
                            } 

                            int temp = i + num + 1;
                            
                            auto check = find_if(springs.begin() + temp, springs.end(), [] (char c) { return (c != '.'); });
                            if(check != springs.end()) temp = check - springs.begin();
                            
                            if((temp + order[orderPos + 1]) <= lineSize) {
                                //cout << "new string starts at pos " << temp << endl;
                                Node node = Node(orderPos + 1, temp, sumGroups);
                                localSum += node.findNext();
                            }
                        }
                    }
                }
                if(springs[i] == '#') break;
            }
        }
        return localSum;
    }
    
};

vector<int> Node::order;
string Node::springs;
vector<Node> Node::nodes;