#include <stdio.h>
#include <stdlib.h>
void get_first_char(char* character) {
	
	scanf("%c", character);
	
	char temp_char = character[0];
	
	while (temp_char != '\n') {
		scanf("%c", &temp_char);
	}

}

void process_command(char command) {
	switch (command) {
	case '0': {
		printf("Help\n");
		break;
	}
	case '1': {
		printf("Append text to line\n");
		break;
	}
	case '2': {
		printf("Start new line\n");
		break;
	}
	case '3': {
		printf("Save text into file\n");
		break;
	}
	case '4': {
		printf("Load text from file\n");
		break;
	}
	case '5': {
		printf("Print text to console\n");
		break;
	}
	case '6': {
		printf("Insert text by line and index at line\n");
		break;
	}
	case '7': {
		printf("Search for substrings in text\n");
		break;
	}
	}
}

int main() {
	int debug = 0;

	if (debug) {
		// something I want to test
		return 0;
	}
	
	printf("Welcome to our text editor\n");
	
	while (1) {

		printf("Enter command you want to execute > ");
		char command;
		get_first_char(&command);
		printf("Your command is %c\n", command);
		if (command == '\n') {
			printf("Program exited\n");
			return 0;
		}
		process_command(command);
	}
	return 0;
}