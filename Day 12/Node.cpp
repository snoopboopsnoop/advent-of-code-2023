#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    static vector<int> order; // static order vector
    static string springs; // static spring record
    static vector<Node> nodes; // list of nodes for memoization

    int num; // which number to look for
    int orderPos; // current index of order vector
    int springPos; // which index of the string does this node start with
    unsigned long long localSum; // arrangements from this node

    Node(int paramOPos, int paramSPos) {
        localSum = 0;
        orderPos = paramOPos;
        num = order[orderPos];
        springPos = paramSPos;
    }

    long long findNext() {
        // the one i time i put size in a variable lmao
        size_t lineSize = springs.size();
        for(int i = springPos; i + num <= lineSize; ++i) {
            if(springs[i] != '.') { // found start of possible arrangement
                if(find(springs.begin() + i, springs.begin() + i + num, '.') == springs.begin() + i + num) { // check range of length num is valid
                    if((i + num) == lineSize || springs[i + num] != '#') { // check ahead is not a #
                        if(i == 0 || springs[i - 1] != '#') { // check behind is not a #
                            if(orderPos + 1 == order.size()) { // if last value to find
                                if(find(springs.begin() + num + i, springs.end(), '#') == springs.end()) { // if no # after, then valid path
                                    ++localSum;
                                }
                                if(springs[i] == '#') break;
                                continue;
                            } 

                            int temp = i + num + 1;
                            
                            // check -> next non . index
                            auto check = find_if(springs.begin() + temp, springs.end(), [] (char c) { return (c != '.'); });
                            if(check != springs.end()) temp = check - springs.begin();
                            
                            // checks for a valid size
                            if((temp + order[orderPos + 1]) <= lineSize) {
                                bool found = false;
                                // look for existing node and if exists then return its sum
                                for(Node node : nodes) {
                                    if(node.orderPos == orderPos + 1 && node.springPos == temp) {
                                        localSum += node.localSum;
                                        found = true;
                                        break;
                                    }
                                }
                                // doesn't exist, create a new one
                                if(!found) {
                                    Node node = Node(orderPos + 1, temp);
                                    localSum += node.findNext();
                                    nodes.push_back(node);
                                }
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