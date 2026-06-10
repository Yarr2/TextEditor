#pragma once
struct node {
	char value;
	struct node* pointer;
};

struct string {
	struct node* start;
	struct node* finish;
};
void create_string(struct string* string);
void add_character(struct string* string, char character);
void push_front(struct string* string, struct string* new_string);
void push_back(struct string* string, struct string* new_string);
void print_string(struct string* string);
void insert_text_string(struct string* string, int index, struct string* text, struct data* data, struct stack* stack);
void insert_replacement_string(struct string* string, int index, struct string* text, struct data* data, struct stack* stack);
void destroy_string(struct string* string);
void save_to_file(struct string* string, FILE* file);
void search_for_substring(struct string* string, struct string* substring, int line_index, int* counter);
void delete_inside_string(struct string* string, int index, int number_of_symbols, struct data* data, struct stack* stack);
void copy_from_string(struct string* string, int index, int number_of_symbolls, struct string* copy_buffer);
void copy_string(struct string* original, struct string* copy);