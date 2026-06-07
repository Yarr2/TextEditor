#include <stdio.h>
#include <stdlib.h>
#include "Text.h"
#include "String.h"
#include <stdbool.h>

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

void append_text(struct text* text) {
	printf("Enter text you want to append > ");
	char character;
	scanf_s("%c", &character, 1);
	while (character != '\n') {
		add_character(text->finish->value, character);
		scanf_s("%c", &character, 1);
	}
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

void insert_into_text(struct text* text) {
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
	insert_text(text, line, index, string);
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
void delete_from_text(struct text* text) {
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

	delete_inside_text(text, line, index, number_of_symbols);


}

void undo_commands(struct text* text) {
	printf("Undo command, not implemented\n");
}

void redo_commands(struct text* text) {
	printf("Redo command, not implemented\n");
}

void cut_symbols(struct text* text) {
	printf("Cut command, not implemented\n");
}

void paste_symbols(struct text* text) {
	printf("Paste command, not implemented\n");
}

void copy_symbols(struct text* text) {
	printf("Copy symbols, not implemented\n");
}

void insert_with_replacement(struct text* text) {
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
	insert_replacement_text(text, line, index, string);
}