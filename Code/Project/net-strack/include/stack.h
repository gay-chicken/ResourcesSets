#ifndef STACK_H
#define STACK_H

#include <stdint.h>

#define SP_NULL 0
#define SP_ETH 1
#define SP_ARP 2
#define SP_IPv4 3
#define SP_IPv6 4
#define SP_ICMP 5
#define SP_TCP 6
#define SP_UDP 7

typedef struct stack_node_t {
    int top_type;
    uint8_t protocol;
    void *data;
    struct stack_node_t *next;
    struct stack_node_t *prev;
} StackNode;

typedef struct stack_t {
    StackNode *bottom;
    StackNode *top;
    int size;
} Stack;

Stack *stack_new();
void stack_push(Stack *stack, void *data, uint8_t protocol, int top_type);
StackNode *stack_pop(Stack *stack);
StackNode *stack_peek(const Stack *stack); // 获取栈顶元素

#endif // end of STACK_H