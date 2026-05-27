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
void insert_text_string(struct string* string, int index, struct string* text) {
	if (string->start == string->finish) {
		string->start = text->start;
		string->finish = text->finish;
		return;
	}
	
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

	if (temp == NULL) {
		string->finish = text->finish;
	}
	print_string(string);
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