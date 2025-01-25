#define RED false
#define BLACK true

struct Node {
    int value;
    bool color; // red(false) or black(true)
    Node* left;
    Node* right;
};
