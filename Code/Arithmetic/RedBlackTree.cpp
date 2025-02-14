#include <iostream>

struct Node {
    int value;
    bool color;
    Node* left;
    Node* right;

    enum {
        RED = true,
        BLACK = false
    };
};


int main() {
    Node node;
    node.color = Node::RED;

    std::cout << node.color << std::endl;
}