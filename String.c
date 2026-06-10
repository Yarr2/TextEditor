#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"
struct node {
	char value;
	struct node* pointer;
};

struct string {
	struct node* start;
	struct node* finish;
};
void create_string(struct string* string) {
	struct node* start = (struct node*)malloc(sizeof(struct node));
	start->pointer = NULL;
	start->value = '\0';
	string->finish = start;
	string->start = start;

}
void add_character(struct string* string, char character) {
	struct node* node = (struct node*)malloc(sizeof(struct node));
	node->value = '\0';
	node->pointer = NULL;
	string->finish->value = character;
	string->finish->pointer = node;
	string->finish = node;
}  

void push_front(struct string* string, struct string* new_string) {
	new_string->finish->value = string->start->value;
	new_string->finish->pointer = string->start->pointer;

	free(string->start);
	string->start = new_string->start;
}
void push_back(struct string* string, struct string* new_string) {
	string->finish->pointer = new_string->start->pointer;
	string->finish->value = new_string->start->value;
	free(new_string->start);
	string->finish = new_string->finish;
}


void print_string(struct string* string) {
	struct node* node = string->start;

	while (node != string->finish) {
		printf("%c", node->value);
		node = node->pointer;
	}
}
int get_size(struct string* string) {
	int counter = 0;
	struct node* node = string->start;
	while (node->pointer != NULL) {
		counter++;
		node = node->pointer;
	}
	return counter;
}
void clear_string(struct string* string) {
	struct node* node = string->start;
	struct node* temp;
	while (node->pointer != NULL) {
		temp = node->pointer;
		free(node);
		node = temp;
	}
	free(node);
	struct node* new_node = (struct node*)malloc(sizeof(struct node));
	new_node->pointer = NULL;
	new_node->value = '\0';

	string->start = new_node;
	string->finish = new_node;
}

void insert_text_string(struct string* string, int index, struct string* text, struct data* data, struct stack* stack) {
	data->number_of_symbols = get_size(text);
	data->string = NULL;
	data->command = Delete;

	if (string->start == string->finish) {
		string->start = text->start;
		string->finish = text->finish;
		data->index = 0;
		push(stack, data);
		return;
	}
	
	if (index == 0) {
		push_front(string, text);
		data->index = 0;
		push(stack, data);
		return;
	}

	struct node* node = string->start;
	int counter = 0;
	while (counter < index - 1 && node->pointer != NULL) {
		counter++;
		node = node->pointer;
	}
	if (counter != index - 1) {
		printf("There is no such index to insert text\n");
		return;
	}
	
	struct node* temp = node->pointer;
	node->pointer = text->start;
	text->finish->pointer = temp;

	if (temp == NULL) {
		string->finish = text->finish;
	}
	data->index = index;
	push(stack, data);
}

void insert_replacement_string(struct string* string, int index, struct string* text, struct data* data, struct stack* stack) {
	int current_index = 0;
	struct node* node = string->start;
	while (current_index < index && node->pointer != NULL) {
		node = node->pointer;
		current_index++;
	}
	if (current_index < index) {
		printf("There is no such index at this line");
		return;
	}
	data->command = InsertWithReplacment;
	data->index = index;
	data->number_of_symbols = get_size(text);
	data->string = (struct string*)malloc(sizeof(struct string));
	create_string(data->string);

	struct node* insert_node = text->start;
	while (node->pointer != NULL && insert_node->pointer != NULL) {
		add_character(data->string, node->value);
		node->value = insert_node->value;
		node = node->pointer;
		insert_node = insert_node->pointer;
	}
	while (insert_node->pointer != NULL) {
		add_character(string, insert_node->value);
		insert_node = insert_node->pointer;
	}
	push(stack, data);
}

void destroy_string(struct string* string) {
	if (string == NULL) {
		return;
	}
	struct node* node = string->start;
	struct node* temp;
	while (node->pointer != NULL) {
		temp = node->pointer;
		free(node);
		node = temp;
	}
	free(node);
	free(string);
}
void save_to_file(struct string* string, FILE* file) {
	struct node* node = string->start;
	while (node->pointer != NULL) {
		fputc(node->value, file);
		node = node->pointer;
	}
}

void copy_from_string(struct string* string, int index, int number_of_symbolls, struct string* copy_buffer) {
	int current_index = 0;
	struct node* node = string->start;
	while (current_index < index && node->pointer != NULL) {
		node = node->pointer;
		current_index++;
	}
	if (current_index < index) {
		printf("There is no such index at this line");
		return;
	}

	clear_string(copy_buffer);
	int counter = 0;
	while (counter < number_of_symbolls && node->pointer != NULL) {
		add_character(copy_buffer, node->value);
		node = node->pointer;
		counter++;
	}
}

void search_for_substring(struct string* string, struct string* substring, int line_index, int* substring_counter) {
	struct node* node = string->start;
	int counter = 0;
	while (node->pointer != NULL) {
		if (node->value == substring->start->value) {
			struct node* string_node = node;
			struct node* substring_node = substring->start;
			while (substring_node->pointer != NULL) {
				if (string_node->value == substring_node->value) {
					string_node = string_node->pointer;
					substring_node = substring_node->pointer;
					continue;
				}
				break;
			}
			if (substring_node == substring->finish) {
				substring_counter[0]++;
				printf("%d %d\n", line_index, counter);
			}
		}
		counter++;
		node = node->pointer;
	}
}
void delete_inside_string(struct string* string, int index, int number_of_symbols, struct data* data, struct stack* stack) {
	if (string == NULL || string->start->pointer == NULL) {
		return;
	}
	data->index = index;
	data->command = Insert;
	data->number_of_symbols = 0;
	data->string = (struct string*)malloc(sizeof(struct string));
	if (data->string != NULL) {
		create_string(data->string);
	}

	struct node* prev_node = NULL;
	struct node* current_node = string->start;
	int current_index = 0;

	while (current_index < index && current_node != NULL) {
		prev_node = current_node;
		current_node = current_node->pointer;
		current_index++;
	}
	if (current_index < index || current_node == NULL) {
		printf("There is no such index at this line\n");
		return;
	}
	int counter = 0;
	while (counter < number_of_symbols && current_node != NULL) {
		struct node* next_node = current_node->pointer;

		if (data->string != NULL) {
			add_character(data->string, current_node->value);
			data->number_of_symbols++;
		}

		free(current_node);
		current_node = next_node;
		counter++;
	}

	if (index == 0) {
		string->start = current_node;
	}
	else {
		prev_node->pointer = current_node;
	}

	push(stack, data);
}
void copy_string(struct string* original, struct string* copy) {
	clear_string(copy);
	struct node* node = original->start;
	while (node->pointer != NULL) {
		add_character(copy, node->value);
		node = node->pointer;
	}
}