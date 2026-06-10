#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "String.h"
#include "Stack.h"

struct line {
	struct string* value;
	struct line* pointer;
};

struct text {
	struct line* start;
	struct line* finish;
};

void create_text(struct text* text) {
	struct line* start = (struct line*)malloc(sizeof(struct line));
	start->pointer = NULL;
	struct string* string = (struct string*)malloc(sizeof(struct string));
	create_string(string);
	start->value = string;
	text->finish = start;
	text->start = start;
}
void clear(struct text* text) {
	struct line* line = text->start;
	while (line != NULL) {
		struct line* next = line->pointer;
		destroy_string(line->value);
		free(line);
		line = next;
	}
	create_text(text);
}
void add_line(struct text* text) {
	struct line* new_line = (struct line*)malloc(sizeof(struct line));
	new_line->pointer = NULL;

	struct string* string = (struct string*)malloc(sizeof(struct string));
	create_string(string);
	new_line->value = string;

	text->finish->pointer = new_line;
	text->finish = new_line;
}
void print_text(struct text* text) {
	struct line* line = text->start;
	while (line->pointer != NULL) {
		print_string(line->value);
		printf("\n");
		line = line->pointer;
	}
	print_string(line->value);
	printf("\n");

}
void insert_text(struct text* text, int line, int index, struct string* string, struct stack* stack) {
	struct line* node = text->start;
	int counter = 0;
	while (counter < line && node->pointer != NULL) {
		counter++;
		node = node->pointer;
	}
	if (counter == line) {
		struct data* command = (struct data*)malloc(sizeof(struct data));
		command->line = line;
		insert_text_string(node->value, index, string, command, stack);
		free(command);
		return;
	}
	else {
		printf("There is no line with index %d\n", line);
		return;
	}
}
void insert_replacement_text(struct text* text, int line, int index, struct string* string, struct stack* stack) {
	struct line* node = text->start;
	int counter = 0;
	while (counter < line && node->pointer != NULL) {
		counter++;
		node = node->pointer;
	}
	if (counter == line) {
		struct data* command = (struct data*)malloc(sizeof(struct data));
		command->line = line;
		insert_replacement_string(node->value, index, string, command, stack);
		free(command);
	}
	else {
		printf("There is no line with index %d\n", line);
		return;
	}
}
void destroy_text(struct text* text) {
	struct line* line = text->start;
	while (line != NULL) {
		struct line* next = line->pointer;
		destroy_string(line->value);
		free(line);
		line = next;
	}
	free(text);
}
void search_in_text(struct text* text, struct string* string) {
	struct line* line = text->start;
	int* counter = malloc(sizeof(int));
	counter[0] = 0;
	int line_counter = 0;
	while (line != NULL) {
		search_for_substring(line->value, string, line_counter, counter);
		line = line->pointer;
		line_counter++;
	}
	if (counter[0] == 0) {
		printf("Substring not found\n");
	}
}


void delete_inside_text(struct text* text, int line, int index, int number_of_symbols, struct stack* stack) {
	struct line* node = text->start;
	int counter = 0;
	while (counter < line && node->pointer != NULL) {
		counter++;
		node = node->pointer;
	}
	if (counter == line) {
		struct data* command = (struct data*)malloc(sizeof(struct data));
		command->line = line;
		delete_inside_string(node->value, index, number_of_symbols, command, stack);
		free(command);
		return;
	}
	else {
		printf("There is no line with index %d\n", line);
		return;
	}
}

void copy_from_text(struct text* text, int line, int index, int number_of_symbolls, struct string* copy_buffer) {
	struct line* node = text->start;
	int counter = 0;
	while (counter < line && node->pointer != NULL) {
		counter++;
		node = node->pointer;
	}
	if (counter == line) {
		copy_from_string(node->value, index, number_of_symbolls, copy_buffer);
		return;
	}
	else {
		printf("There is no line with index %d\n", line);
		return;
	}
}

void load_text(struct text* text, char* path) {
	FILE* file;
	file = fopen(path, "r");
	if (file == NULL) {
		printf("Such file does not exist\n");
		return;
	}

	clear(text);
	int character;
	character = fgetc(file);
	while (character != EOF) {// EndOfFile value is -1
		if (character == '\n') {
			add_line(text);
		}
		else {
			add_character(text->finish->value, (char)character);
		}
		character = fgetc(file);
	}
	fclose(file);

}
void save_text(struct text* text, char* path) {
	FILE* file;
	file = fopen(path, "w");
	if (file != NULL) {
		struct line* line = text->start;
		while (line->pointer != NULL) {
			save_to_file(line->value, file);
			fputc('\n', file);
			line = line->pointer;
		}
		save_to_file(line->value, file);
		fclose(file);
		printf("Succesfully saved text into file\n");
	}
	else {
		printf("Error with filepath");
	}
}
