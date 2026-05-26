#include <stdio.h>
#include <stdlib.h>
#include "Text.c"


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
		char character;
		scanf("%c", &character);
		printf("File name is \"");
		while (character != '\n') {
			printf("%c", character);
			scanf("%c", &character);
		}
		printf("\"\n");
		break;
	}
	case '4': {
		printf("Load text from file\n");
		printf("Enter file name > ");
		char character;
		scanf("%c", &character);
		printf("File name is \"");
		while (character != '\n') {
			printf("%c", character);
			scanf("%c", &character);
		}
		printf("\"\n");
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
			printf("Incorrect input\n");
			return;
		}
		while (character != '\n') {
			scanf("%c", &character);
		}
		printf("Enter text to insert > ");
		scanf("%c", &character);
		printf("Line is %d\n", line);
		printf("Index is %d\n", index);
		printf("Text to insert is \"");
		while (character != '\n') {
			printf("%c", character);
			scanf("%c", &character);
		}
		printf("\"\n");
		break;
	}
	case '7': {
		printf("Search for substrings in text\n");
		printf("Enter substring > ");
		char character;
		scanf("%c", &character);
		printf("Substring is \"");
		while (character != '\n') {
			printf("%c", character);
			scanf("%c", &character);
		}
		printf("\"\n");
		break;
	}
	}
}

int main() {
	int debug = 0;
	struct text* text = (struct text*)malloc(sizeof(text));
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
		if (command == '\n') {
			printf("Program exited\n");
			return 0;
		}
		process_command(command,text);
	}
	return 0;
}