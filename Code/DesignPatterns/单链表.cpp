#include <iostream>

using namespace std;

class Node {
public:
    Node(int);
    void push_back(int value);
    void show();
    int m_value;
    Node* next;
};

Node::Node(int value) {
    m_value = value;
    next = nullptr;
}

void Node::push_back(int value) {
    Node* node = new Node(value);
    Node* now_ptr = this;
    while(now_ptr->next != nullptr)
        now_ptr = now_ptr->next;
    now_ptr->next = node;
}

void Node::show() {
    Node* ptr = this;
    while(ptr != nullptr) {
        cout << ptr->m_value << " ";
        ptr = ptr->next;
    }
}

int main() {
    Node node(5);
    node.push_back(1);
    node.push_back(2);
    node.push_back(3);
    node.show();
}