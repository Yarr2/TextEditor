#include <stdlib.h>
#include <stdio.h>


struct data {
	int value;
};

struct stack {
	struct data* values;
	int size;
	int max_size;
};
struct stack* create_stack() {
	struct stack* stack = (struct stack*)malloc(sizeof(struct stack));
	if (stack == NULL) return NULL;

	stack->size = 0;
	stack->max_size = 8;
	stack->values = (struct data*)malloc(sizeof(struct data) * stack->max_size);
	return stack;
}

void add_space(struct stack* stack) {
	stack->max_size = stack->max_size * 2;
	stack->values = (struct data*)realloc(stack->values, sizeof(struct data) * stack->max_size);
}
void destroy_stack(struct stack* stack) {
	if (stack != NULL) {
		free(stack->values);
		free(stack);
	}
}

void push(struct stack* stack, struct data* data) {
	if (stack->size == stack->max_size) {
		add_space(stack);
	}
	stack->values[stack->size] = *data;
	stack->size++;
}

void pop(struct stack* stack, struct data* out_data) {
	if (stack->size == 0) {
		printf("Stack is empty\n");
		return;
	}
	stack->size--;
	*out_data = stack->values[stack->size];
}

void peek(struct stack* stack, struct data* out_data) {
	if (stack->size == 0) {
		printf("Stack is empty\n");
		return;
	}
	*out_data = stack->values[stack->size - 1];
}

void print_stack(struct stack* stack) {
	for (int i = stack->size - 1; i >= 0; i--) {
		printf("%d. value - %d\n", stack->size - i, stack->values[i].value);
	}
}