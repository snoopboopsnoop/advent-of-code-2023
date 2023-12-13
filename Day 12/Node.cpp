#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <sstream>
#include <algorithm>

using namespace std;

struct Node {
    int orderPos; // which index of order does this node look at
    int springPos; // which index of the string does this node start with
    static int perms;

    Node(int order, int spring) {
        orderPos = order;
        springPos = spring;
    }


};

int Node::perms = 0;