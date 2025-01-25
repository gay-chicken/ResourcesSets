#include <stdlib.h>

#include "log.h"
#include "stack.h"

Stack *stack_new()
{
    Stack *stack = malloc(sizeof(Stack));
    if (!stack) LOG_ERROR("stack_new", "Allocation memory failed!");

    stack->top = NULL;
    stack->bottom = NULL;
    stack->size = 0;
    return stack;
}

void stack_push(Stack *stack, void *data, uint8_t protocol, int top_type)
{
    StackNode *node = malloc(sizeof(StackNode)); // Exception: Unknown signal
    if (!node) LOG_ERROR("stack_push", "Allocation memory failed!"); // Unable to do

    node->data = data;
    node->protocol = protocol;
    node->top_type = top_type;
    node->prev = NULL;
    node->next = NULL;

    if (stack->bottom == NULL) {
        stack->bottom = node;
    }
    if (stack->top != NULL) {
        node->next = stack->top;
        stack->top->prev = node;
    }
    stack->top = node;
    stack->size++;
}

StackNode *stack_pop(Stack *stack)
{
    if (stack->top == NULL || stack->size == 0) return NULL;

    StackNode *node = stack->top;
    if (stack->bottom == stack->top) {
        stack->bottom = NULL;
    }
    stack->top = stack->top->next;
    if (stack->top) {  // Protect against NULL dereference
        stack->top->prev = NULL;
    }
    stack->size--;
    return node;
}

StackNode *stack_peek(const Stack *stack)
{
    return stack->top;
}
