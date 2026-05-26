#include <stdio.h>
#include <stdlib.h>

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
	new_string->finish->pointer = string->start->pointer;
	new_string->finish->value = string->start->value;
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
void insert_text_string(struct string* string, int index, struct string* text) {
	if (index == 0) {
		push_front(string, text);
		return;
	}

	struct node* node = string->start;
	int counter = 0;
	while (counter < index - 1 && node->pointer != NULL) {
		counter++;
		node = node->pointer;
	}
	struct node* temp = node->pointer;
	node->pointer = text->start;
	text->finish->pointer = temp;
}

void destroy_string(struct string* string) {
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