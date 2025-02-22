#include <stdio.h>
#include <stdlib.h>

struct Node {
    void (*p)();
    struct Node* next;
};

#define Fun(T) \
void f##T() { \
    printf("func "#T"\n"); \
}

Fun(1)
Fun(2)
Fun(3)

int main() {
    struct Node *head = malloc(sizeof(struct Node) * 3);
    struct Node *curr = head;
    void (*fs[])() = {f1, f2, f3};

    for(int i = 0; i < 3; ++i) {
        curr->p = fs[i];
        curr = curr->next; // next == ???
    }

    curr = head;
    for(int i = 0; i < 3; ++i) {
        curr->p();
        curr = curr->next;
    }
    free(head);
}