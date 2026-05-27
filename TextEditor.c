#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Text.h"
#include "String.h"

void get_first_char(char* character) {
	
	scanf("%c", character);
	
	char temp_char = character[0];
	
	while (temp_char != '\n') {
		scanf("%c", &temp_char);
	}

}

void process_command(char command,struct text* text) {
	switch (command) {
	case '0': {
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
		printf("Enter - to exit program\n");
		break;
	}
	case '1': {
		printf("Append text to line\n");
		printf("Enter text you want to append > ");
		char character;
		scanf("%c", &character);
		while (character != '\n') {
			add_character(text->finish->value, character);
			scanf("%c", &character);
		}
		break;
	}
	case '2': {
		printf("Start new line\n");
		add_line(text);
		break;
	}
	case '3': {
		printf("Save text into file\n");
		printf("Enter file name > ");
		char* path = malloc(sizeof(char)*260);
		scanf("%c", &path[0]);
		int counter = 1;
		while (path[counter - 1] != '\n' && counter < 260) {
			scanf("%c", &path[counter]);
			counter++;
		}
		path[counter - 1] = '\0';

		save_text(text, path);
		free(path);
		break;
	}
	case '4': {
		printf("Load text from file\n");
		printf("Enter file name > ");
		char* path = malloc(sizeof(char) * 260);
		scanf("%c", &path[0]);
		int counter = 1;
		while (path[counter - 1] != '\n' && counter < 260) {
			scanf("%c", &path[counter]);
			counter++;
		}
		path[counter - 1] = '\0';

		load_text(text, path);
		free(path);
		break;
	}
	case '5': {
		printf("Print text to console:\n");
		print_text(text);
		break;
	}
	case '6': {
		printf("Insert text by line and index at line\n");
		printf("Enter line and index(format \"5 4\") > ");
		int line;
		int index;
		char character = '1';
		if (scanf("%d %d", &line, &index) != 2) {
			char temp_char;
			scanf("%c", &temp_char);
			while (temp_char != '\n') {
				scanf("%c", &temp_char);
			}
			printf("Incorrect input\n");
			return;
		}
		while (character != '\n') {
			scanf("%c", &character);
		}
		struct string* string = (struct string*)malloc(sizeof(struct string));
		create_string(string);
		printf("Enter text to insert > ");
		scanf("%c", &character);
		while (character != '\n') {
			add_character(string, character);
			scanf("%c", &character);
		} 
		insert_text(text, line, index, string);
		break;
	}
	case '7': {
		printf("Search for substrings in text\n");
		printf("Enter substring > ");
		char character;
		struct string* string = (struct string*)malloc(sizeof(struct string));
		create_string(string);
		scanf("%c", &character);
		while (character != '\n') {
			add_character(string, character);
			scanf("%c", &character);
		}
		search_in_text(text, string);
		break;
	}
	}
}

int main() {
	int debug = 0;
	struct text* text = (struct text*)malloc(sizeof(struct text));
	create_text(text);

	if (debug) {
		printf("DEBUG MODE");
		return 0;
	}
	
	printf("Welcome to our text editor\n");
	
	while (1) {

		printf("Enter command you want to execute(0 for help) > ");
		char command;
		get_first_char(&command);
		if (command == 'P') {
			printf("Program exited\n");
			destroy_text(text);
			return 0;
		}
		process_command(command,text);
	}
	destroy_text(text);
	return 0;
}