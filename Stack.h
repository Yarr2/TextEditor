#pragma once

enum Command {
	InsertWithReplacment,
	Insert,
	Delete
};

struct data {
	enum Command command;
	int line;
	int index;
	int number_of_symbols;
	struct string* string;
};

struct stack {
	struct data* values;
	int size;
	int max_size;
};

struct stack* create_stack();
void destroy_stack(struct stack* stack);
void push(struct stack* stack, struct data* data);
void pop(struct stack* stack, struct data* data);
void peek(struct stack* stack, struct data* data);
void print_stack(struct stack* stack);