#include <stdio.h>
#include <stdlib.h>
#include "Text.h"
#include "String.h"
#include <stdbool.h>
#include "Stack.h"

void help() {
	printf("Help\n");
	printf("Following commands are avaliable:\n");
	printf("0 - help, transfers you to this window\n");
	printf("1 - append text to current line\n");
	printf("2 - starts new line\n");
	printf("3 - saves text to given file\n");
	printf("4 - loads text from given file\n");
	printf("5 - prints current text\n");
	printf("6 - Insert text by line and index\n");
	printf("7 - search for a substring\n");
	printf("P - to exit program\n");
}

void append_text(struct text* text, struct stack* stack) {
	

	int index = 0;
	struct node* node = text->finish->value->start;
	while (node != text->finish->value->finish) {
		node = node->pointer;
		index++;
	}
	printf("Enter text you want to append > ");
	char character;
	scanf_s("%c", &character, 1);
	int counter = 0;
	while (character != '\n') {
		counter++;
		add_character(text->finish->value, character);
		scanf_s("%c", &character, 1);
	}
	int line_index = 0;
	struct line* line = text->start;
	while (line != text->finish) {
		line = line->pointer;
		line_index++;
	}
	struct data* delete = (struct data*)malloc(sizeof(struct data));
	delete->command = Delete;
	delete->number_of_symbols = counter;
	delete->line = line_index;
	delete->index = index;
	push(stack, delete);
	free(delete);

}

void start_new_line(struct text* text) {
	printf("Starting new line\n");
	add_line(text);
}

void save_text_to_file(struct text* text) {
	printf("Save text into file\n");
	printf("Enter file name > ");
	char* path = malloc(sizeof(char) * 260);
	scanf_s("%c", &path[0], 1);
	int counter = 1;
	while (path[counter - 1] != '\n' && counter < 260) {
		scanf_s("%c", &path[counter], 1);
		counter++;
	}
	path[counter - 1] = '\0';

	save_text(text, path);
	free(path);
}

void load_from_file(struct text* text) {
	printf("Load text from file\n");
	printf("Enter file name > ");
	char* path = malloc(sizeof(char) * 260);
	scanf_s("%c", &path[0], 1);
	int counter = 1;
	while (path[counter - 1] != '\n' && counter < 260) {
		scanf_s("%c", &path[counter], 1);
		counter++;
	}
	path[counter - 1] = '\0';

	load_text(text, path);
	free(path);
}

void insert_into_text(struct text* text, struct stack* stack) {
	printf("Insert text by line and index at line\n");
	printf("Enter line and index(format \"5 4\") > ");
	int line;
	int index;
	char character = '1';
	if (scanf_s("%d %d", &line, &index) != 2) {
		char temp_char;
		scanf_s("%c", &temp_char, 1);
		while (temp_char != '\n') {
			scanf_s("%c", &temp_char, 1);
		}
		printf("Incorrect input\n");
		return;
	}
	while (character != '\n') {
		scanf_s("%c", &character, 1);
	}
	struct string* string = (struct string*)malloc(sizeof(struct string));
	create_string(string);
	printf("Enter text to insert > ");
	scanf_s("%c", &character, 1);
	while (character != '\n') {
		add_character(string, character);
		scanf_s("%c", &character, 1);
	}
	insert_text(text, line, index, string, stack);
}

void search_substring(struct text* text) {
	printf("Search for substrings in text\n");
	printf("Enter substring > ");
	char character;
	struct string* string = (struct string*)malloc(sizeof(struct string));
	create_string(string);
	scanf_s("%c", &character, 1);
	while (character != '\n') {
		add_character(string, character);
		scanf_s("%c", &character, 1);
	}
	search_in_text(text, string);
}
void delete_from_text(struct text* text, struct stack* stack) {
	int line;
	int index;
	int number_of_symbols;
	printf("Enter line,index and number of symbols > ");    
	if (scanf_s("%d %d %d", &line, &index, &number_of_symbols) != 3) {
		char temp_char;
		scanf_s("%c", &temp_char, 1);
		while (temp_char != '\n') {
			scanf_s("%c", &temp_char, 1);
		}
		printf("Incorrect input\n");
		return;
	}
	char temp_char;
	scanf_s("%c", &temp_char, 1);
	while (temp_char != '\n') {
		scanf_s("%c", &temp_char, 1);
	}

	delete_inside_text(text, line, index, number_of_symbols, stack);


}

void undo_commands(struct text* text, struct stack* stack, struct stack* redo_stack) {
	printf("Undo command\n");
	int number_of_operations = 0;
	printf("Enter number of operations to undo > ");
	scanf_s("%d", &number_of_operations, 1);
	char character;
	scanf_s("%c", &character, 1);
	while (character != '\n') {
		scanf_s("%c", &character, 1);
	}
	if (stack->size == 0) {
		printf("There are no commands to undo\n");
		return;
	}

	struct data* command = (struct data*)malloc(sizeof(struct data));
	for (int i = 0; i < number_of_operations; i++) {
		pop(stack, command);
		switch (command->command) {
		case Delete: {
			delete_inside_text(text, command->line, command->index, command->number_of_symbols, redo_stack);
			break;
		}
		case Insert: {
			insert_text(text, command->line, command->index, command->string, redo_stack);
			break;
		} 
		case InsertWithReplacment: {
			delete_inside_text(text, command->line, command->index, command->number_of_symbols, redo_stack);
			insert_text(text, command->line, command->index, command->string, redo_stack);
			struct data* insert_with = (struct data*)malloc(sizeof(struct data));
			insert_with->command = InsertWithReplacment;
			push(redo_stack, insert_with);
			break;
		}
		default: {
			printf("All available to undo commands were undone\n");
			return;
		}
		}
	}
}

void redo_commands(struct text* text, struct stack* stack, struct stack* redo_stack) {
	printf("Redo command\n");
	int number_of_operations = 0;
	printf("Enter number of operations to redo > ");
	scanf_s("%d", &number_of_operations, 1);
	char character;
	scanf_s("%c", &character, 1);
	while (character != '\n') {
		scanf_s("%c", &character, 1);
	}
	if (redo_stack->size == 0) {
		printf("There are no commands to redo\n");
		return;
	}
	struct data* command = (struct data*)malloc(sizeof(struct data));
	for (int i = 0; i < number_of_operations; i++) {
		pop(redo_stack, command);
		switch (command->command) {
		case Delete: {
			delete_inside_text(text, command->line, command->index, command->number_of_symbols, stack);
			break;
		}
		case Insert: {
			insert_text(text, command->line, command->index, command->string, stack);
			break;
		}
		case InsertWithReplacment: {
			i = i - 2; // I add two commands in undo section, so now  I need to execute two more
			break;
		}
		default: {
			printf("All available to redo commands were undone\n");
			return;
		}
		}
	}

}

void cut_symbols(struct text* text, struct string* copy_buffer, struct stack* stack) {
	printf("Cut command \n");
	int line;
	int index;
	int number_of_symbols;
	printf("Enter line,index and number of symbols > ");
	if (scanf_s("%d %d %d", &line, &index, &number_of_symbols) != 3) {
		char temp_char;
		scanf_s("%c", &temp_char, 1);
		while (temp_char != '\n') {
			scanf_s("%c", &temp_char, 1);
		}
		printf("Incorrect input\n");
		return;
	}
	char temp_char;
	scanf_s("%c", &temp_char, 1);
	while (temp_char != '\n') {
		scanf_s("%c", &temp_char, 1);
	}
	copy_from_text(text, line, index, number_of_symbols, copy_buffer);
	delete_inside_text(text, line, index, number_of_symbols, stack);
	
}

void paste_symbols(struct text* text, struct string* copy_buffer, struct stack* stack) {
	printf("Paste command\n");
	printf("Enter line and index(format \"5 4\") > ");
	int line;
	int index;
	char character = '1';
	if (scanf_s("%d %d", &line, &index) != 2) {
		char temp_char;
		scanf_s("%c", &temp_char, 1);
		while (temp_char != '\n') {
			scanf_s("%c", &temp_char, 1);
		}
		printf("Incorrect input\n");
		return;
	}
	while (character != '\n') {
		scanf_s("%c", &character, 1);
	}
	struct string* copy_of_buffer = (struct string*)malloc(sizeof(struct string));
	create_string(copy_of_buffer);
	copy_string(copy_buffer, copy_of_buffer);
	insert_text(text, line, index, copy_of_buffer, stack);
}

void copy_symbols(struct text* text, struct string* copy_buffer) {
	printf("Copy symbols\n");
	int line;
	int index;
	int number_of_symbols;
	printf("Enter line,index and number of symbols > ");
	if (scanf_s("%d %d %d", &line, &index, &number_of_symbols) != 3) {
		char temp_char;
		scanf_s("%c", &temp_char, 1);
		while (temp_char != '\n') {
			scanf_s("%c", &temp_char, 1);
		}
		printf("Incorrect input\n");
		return;
	}
	char temp_char;
	scanf_s("%c", &temp_char, 1);
	while (temp_char != '\n') {
		scanf_s("%c", &temp_char, 1);
	}
	copy_from_text(text, line, index, number_of_symbols, copy_buffer);
}

void insert_with_replacement(struct text* text, struct stack* stack) {
	printf("Insert text with replacement by line and index\n");
	printf("Enter line and index(format \"5 4\") > ");
	int line;
	int index;
	char character = '1';
	if (scanf_s("%d %d", &line, &index) != 2) {
		char temp_char;
		scanf_s("%c", &temp_char, 1);
		while (temp_char != '\n') {
			scanf_s("%c", &temp_char, 1);
		}
		printf("Incorrect input\n");
		return;
	}
	while (character != '\n') {
		scanf_s("%c", &character, 1);
	}
	struct string* string = (struct string*)malloc(sizeof(struct string));
	create_string(string);
	printf("Enter text to insert > ");
	scanf_s("%c", &character, 1);
	while (character != '\n') {
		add_character(string, character);
		scanf_s("%c", &character, 1);
	}
	insert_replacement_text(text, line, index, string, stack);
}